#include "bufpool.h"
#include "file_util.h"
#include "my_sys.h"
#include "mysql/service_mysql_alloc.h"

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

void buf::BufPool::write(uchar *buf, uint32_t size, uint64_t tableId, uint32_t pageId, File fd) {
  if (!isExistPage(tableId, pageId)) {
    readFromFile(fd, tableId, pageId);
  }

  Page *page = get(tableId, pageId);
  assert(page != nullptr);

  uint32_t beforeInsertTupleCount = page->pageHeader.tupleCount;
  int insertPosition = PAGE_BODY_SIZE - (beforeInsertTupleCount * size) - (size + 1);
  write_fixed_size_part(buf, size, insertPosition, page);
  page->pageHeader.tupleCount++;
  flush(fd, page, pageId);
}

void buf::BufPool::flush(File fd, Page *page, uint32_t pageId) {
  FileUtil::seek(fd,
                 TABLE_SPACE_START_POSITION + TABLE_SPACE_HEADER_SIZE + SYSTEM_PAGE_SIZE + (PAGE_SIZE * pageId),
                 MY_SEEK_SET,
                 MYF(0)
  );
  uchar *buf = (uchar *)page;
  FileUtil::write(fd, buf, PAGE_SIZE);
}

void buf::BufPool::write_fixed_size_part(uchar *buf, uint32_t size, int position, Page *page) {
  memcpy((page->body + position), buf, size);
}

void buf::BufPool::read(uchar *buf, uint32_t size, int tupleCount, int tableId, int pageId, File fd) {
  if (!isExistPage(tableId, pageId)) {
    // read from File
    readFromFile(fd, tableId, pageId);
  }
  int position = PAGE_BODY_SIZE - (tupleCount * size) - 1;
  Page *page = get(tableId, pageId);
  read_fixed_size_part(buf, size, position, page);
}

void buf::BufPool::read_fixed_size_part(uchar *buf, uint32_t size, int position, Page *page) {
  memcpy(buf, (page->body + position), size);
}

bool buf::BufPool::isExistPage(uint64_t tableId, uint32_t pageId) {
  if(this->elements == nullptr) {
    return false;
  }

  for(Element *element = this->elements; element != nullptr; element = element->next) {
    if (element->tableSpaceId != tableId) {
      continue;
    }
    if (element->page->pageHeader.page_id == pageId) {
      return true;
    }
  }

  return false;
}

bool buf::BufPool::hasNextTuple(uint32_t tupleId, uint64_t tableId, int pageId) {
  Page *page = get(tableId, pageId);
  if (page == nullptr) {
    return false;
  }
  return page->pageHeader.tupleCount > tupleId;
}

Page *buf::BufPool::get(uint64_t tableId, uint32_t pageId) {
  for (Element *element = this->elements; element != nullptr; element = elements->next) {
    if (element->tableSpaceId == tableId && element->page->pageHeader.page_id == pageId) {
      element->refCount++;
      return element->page;
    }
  }
  return nullptr;
}

void buf::BufPool::readFromFile(File fd, uint64_t  tableId, uint32_t pageId) {
  Page *page = TableFileImpl::readPage(fd, pageId);
  Element *element = elements;

  if (elements == nullptr) {
    Element *newElement = (Element *)malloc(sizeof(Element));
    newElement->next = nullptr;
    newElement->refCount = 0;
    newElement->tableSpaceId = tableId;
    newElement->page = page;
    elements = newElement;
    return;
  }

  while(element->next != nullptr) {
    element = element->next;
  }

  Element *newElement = (Element *)malloc(sizeof(Element));
  newElement->next = nullptr;
  newElement->refCount = 0;
  newElement->tableSpaceId = tableId;
  newElement->page = page;

  element->next = newElement;
}
