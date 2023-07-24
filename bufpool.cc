#include "bufpool.h"
#include "file_util.h"
#include "my_sys.h"
#include "mysql/service_mysql_alloc.h"

void buf::BufPool::init_buffer_pool(PSI_memory_key b, int) {
  // TODO: Support More Pages
  Page *p = (Page *)my_malloc(b, sizeof(Page), MYF(MY_WME));
  p->pageHeader.tupleCount = 0;
  this->pages = p;
}

void buf::BufPool::deinit_buffer_pool() {
  my_free(this->pages);
}

void buf::BufPool::write(uchar *buf, uint32_t size, int, int) {
  int beforeInsertTupleCount = this->pages->pageHeader.tupleCount;
  int insertPosition = PAGE_SIZE - (beforeInsertTupleCount * size) - 1;
  write_fixed_size_part(buf, size, insertPosition, 0);
  this->pages->pageHeader.tupleCount++;
}

void buf::BufPool::write_fixed_size_part(uchar *buf, uint32_t size, int position, int) {
  memcpy((this->pages->body + position), buf, size);
}

void buf::BufPool::read(uchar *buf, uint32_t size, int tupleCount, int) {
  int position = PAGE_SIZE - (tupleCount * size) - 1;
  read_fixed_size_part(buf, size, position, 0);
}

void buf::BufPool::read_fixed_size_part(uchar *buf, uint32_t size, int position, int) {
  memcpy(buf, (this->pages->body + position), size);
}
void buf::BufPool::flush(File fd) {
  FileUtil::seek(fd,
                 TABLE_SPACE_START_POSITION + TABLE_SPACE_HEADER_SIZE + SYSTEM_PAGE_SIZE,
                 MY_SEEK_SET,
                 MYF(0)
                 );
  FileUtil::write(fd, this->pages->body, PAGE_SIZE);
}
