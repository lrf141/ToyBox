#include "bufpool.h"
#include "my_sys.h"
#include "mysql/service_mysql_alloc.h"
#include "page.h"
#include "tablespace.h"


void buf::BufPool::init_buffer_pool(PSI_memory_key, int bufPoolSize) {
  this->maxPageCount = bufPoolSize;
}

void buf::BufPool::deinit_buffer_pool() {
  releaseAllPage();
}

void buf::BufPool::releaseAllPage() {
  if (this->elements == nullptr) {
    return;
  }

  for(Element *element = this->elements; element != nullptr;) {
    Element *tmp = element->next;
    free(element);
    element = tmp;
  }
}

void buf::BufPool::readFromFile(tablespace_id tablespaceId, page_id pageId,
                                const char *tablespacePath) {
  tablespace::TablespaceHandler tablespaceHandler =
      tablespace::TablespaceHandler(tablespacePath);
  page::PageHandler pageHandler = page::PageHandler(pageId);
  pageHandler.read(tablespaceHandler.getFileDescriptor());

  Element *newElement = new Element(tablespaceId, pageHandler);
  Element *lastElement = getLastElement();
  if (lastElement == nullptr) {
    this->elements = newElement;
  } else {
    lastElement->next = newElement;
  }
}

buf::Element *buf::BufPool::getLastElement() const {
  Element *element = this->elements;
  if (element == nullptr) {
    return nullptr;
  }
  while(element->next != nullptr) {
    element = element->next;
  }
  return element;
}

bool buf::BufPool::existPage(tablespace_id tablespaceId, page_id pageId) const {
  Element *element = this->elements;
  bool exists = false;
  if (element == nullptr) {
    return false;
  }
  while(true) {
    if (element->tableSpaceId == tablespaceId &&
        element->getPageHandler().getPageHeader().id == pageId) {
      exists = true;
      break;
    }
    if (element->next == nullptr) {
      break;
    }
    element = element->next;
  }
  return exists;
}

buf::Element *buf::BufPool::getElement(tablespace_id tablespaceId,
                                       page_id pageId) {
  Element *element = this->elements;
  if (element == nullptr) {
    return nullptr;
  }
  while(true) {
    if (element->tableSpaceId == tablespaceId &&
        element->getPageHandler().getPageHeader().id == pageId) {
      return element;
    }
    if (element->next == nullptr) {
      break;
    }
    element = element->next;
  }
  return nullptr;
}

void buf::BufPool::read(uchar *buf, buf::ReadDescriptor readDescriptor) {
  tablespace_id tablespaceId = readDescriptor.tablespaceId;
  page_id pageId = readDescriptor.pageId;

  if(!existPage(tablespaceId, pageId)) {
    readFromFile(tablespaceId, pageId, readDescriptor.tablespacePath);
  }

  Element *targetElement = getElement(tablespaceId, pageId);
  assert(targetElement != nullptr);

  page::PageHandler& pageHandler = targetElement->getPageHandler();
  uchar *body = pageHandler.getPage().getPage().body;
  // TODO: calc columnSize
  int columnSize = 4;
  body = body + columnSize * readDescriptor.tupleId;
  for (int i = 0; i < columnSize; i++) {
    *(buf + i) = *(body + i);
  }
}

void buf::BufPool::write(uchar *buf, buf::WriteDescriptor writeDescriptor) {
  tablespace_id tablespaceId = writeDescriptor.tablespaceId;
  page_id pageId = writeDescriptor.pageId;

  if(!existPage(tablespaceId, pageId)) {
    readFromFile(tablespaceId, pageId, writeDescriptor.tablespacePath);
  }

  Element *targetElement = getElement(tablespaceId, pageId);
  assert(targetElement != nullptr);

  page::PageHandler& pageHandler = targetElement->getPageHandler();
  uchar *body = pageHandler.getPage().getPage().body;
  uint64_t lastTupleId = pageHandler.getPage().getPage().header.tupleCount;
  // TODO: calc columnSize
  int columnSize = 4;
  for (int i = 0; i < columnSize; i++) {
    *((body + lastTupleId * columnSize) + i) = *(buf + i);
  }
  pageHandler.getPage().incrementTupleCount();
}

bool buf::BufPool::isLastPage(tablespace_id tablespaceId, page_id pageId,
                               const char *tablespacePath) {
  if(!existPage(tablespaceId, pageId)) {
    readFromFile(tablespaceId, pageId, tablespacePath);
  }
  Element *cursor = getElement(tablespaceId, pageId);
  return cursor->getPageHandler().getPage().getNextPageId() == UINT64_MAX;
}

bool buf::BufPool::isLastTuple(tablespace_id tablespaceId, page_id pageId,
                                uint64_t tupleId, const char *tablespacePath) {
  if(!existPage(tablespaceId, pageId)) {
    readFromFile(tablespaceId, pageId, tablespacePath);
  }
  Element *cursor = getElement(tablespaceId, pageId);
  return cursor->getPageHandler().getPageHeader().tupleCount == tupleId;
}
