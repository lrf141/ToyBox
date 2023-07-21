#include "buffer.h"

void BufferPool::init_buffer_pool(int bufPoolSize) {
  Page *pages = static_cast<Page *>(malloc(sizeof(Page) * bufPoolSize));
  BufPool *bufPool = static_cast<BufPool *>(malloc(sizeof(BufferPool)));
  bufPool->pages = pages;
  BufferPool::bufferPool = bufPool;
}
