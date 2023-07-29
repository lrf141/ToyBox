#ifndef AVID_BUFFER_H
#define AVID_BUFFER_H

#include <stdlib.h>

#include "table_file.h"
#include "page.h"
#include "sql/psi_memory_key.h"
#include "my_inttypes.h"

namespace buf {

struct Element {
  uint64_t tableSpaceId;
  uint64_t refCount;
  Page *page;
  Element *next;
};

typedef struct Element Element;

class BufPool {
 private:
  uint64_t pageCount = 0;
  uint64_t maxPageCount;
  bool isExistPage(uint64_t tableId, uint32_t pageId);
  void write_fixed_size_part(uchar *buf, uint32_t size, int position, Page *page);
  void read_fixed_size_part(uchar *buf, uint32_t size, int position, Page* page);
  void readFromFile(File fd, uint64_t tableId, uint32_t pageId);
  Page *get(uint64_t tableId, uint32_t pageId);
  void releaseAllPage();
 public:
  Element *elements = nullptr;
  Page *pages;
  void init_buffer_pool(PSI_memory_key buf, int bufPoolSize);
  void deinit_buffer_pool();
  void write(uchar *buf, uint32_t size, uint64_t tableId, uint32_t pageId, File fd);
  void read(uchar *buf, uint32_t size, int tupleId, int tableId, int pageId, File fd);
  void flush(File fd, Page *page, uint32_t pageId);
  bool hasNextTuple(uint32_t tupleId, uint64_t tableId, int pageId);
};
}

#endif  // MYSQL_BUFFER_H
