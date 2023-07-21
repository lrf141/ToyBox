#ifndef MYSQL_BUFFER_H
#define MYSQL_BUFFER_H

#include <stdlib.h>

#include "page.h"

typedef struct BufPool BufPool;

struct BufPool {
  Page *pages;
};

class BufferPool {
 private:
  static BufPool *bufferPool;
 public:
  BufferPool() {}
  ~BufferPool() {
    free(bufferPool->pages);
    free(bufferPool);
  }
  void init_buffer_pool(int bufPoolSize);
};

#endif  // MYSQL_BUFFER_H
