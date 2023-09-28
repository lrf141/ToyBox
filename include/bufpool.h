#ifndef TOYBOX_BUFFER_H
#define TOYBOX_BUFFER_H

#include <stdlib.h>

#include "page.h"
#include "page_type.h"
#include "tablespace_type.h"
#include "sql/psi_memory_key.h"
#include "my_inttypes.h"

namespace buf {

struct PageDescriptor {
  tablespace_id tablespaceId;
  page_id pageId;
  char *tablespacePath;
};

struct ReadDescriptor {
  tablespace_id tablespaceId;
  page_id pageId;
  uint64_t tupleId;
  char *tablespacePath;
};

struct WriteDescriptor {
  tablespace_id tablespaceId;
  page_id pageId;
  char *tablespacePath;
};

struct Element {
  uint64_t tableSpaceId;
  uint64_t refCount;
  page::PageHandler pageHandler;
  Element *next;
  Element(tablespace_id tablespaceId, page::PageHandler page)
      : tableSpaceId(tablespaceId),
        refCount(0),
        pageHandler(page),
        next(nullptr) {}
  page::PageHandler& getPageHandler() {
    return pageHandler;
  }
};

typedef struct Element Element;

class BufPool {
 private:
  uint64_t maxPageCount;
  void readFromFile(tablespace_id tablespaceId, page_id pageId,
                    const char *tablespacePath);
  void releaseAllPage();
 public:
  Element *elements = nullptr;
  void init_buffer_pool(PSI_memory_key buf, int bufPoolSize);
  void deinit_buffer_pool();
  void read(uchar *buf, ReadDescriptor readDescriptor);
  void write(uchar *buf, WriteDescriptor writeDescriptor);
  Element* getElement(tablespace_id tablespaceId, page_id pageId);
  bool isLastPage(tablespace_id tablespaceId, page_id pageId, const char *tablespacePath);
  bool isLastTuple(tablespace_id tablespaceId, page_id pageId, uint64_t tupleId, const char *tablespacePath);
  bool existPage(tablespace_id tablespaceId, page_id pageId) const;
  Element *getLastElement() const;
};

}

#endif  // MYSQL_BUFFER_H