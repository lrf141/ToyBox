#include "bufpool.h"
#include "my_sys.h"
#include "mysql/service_mysql_alloc.h"

void buf::BufPool::init_buffer_pool(PSI_memory_key b, int) {
  Page *p = (Page *)my_malloc(b, sizeof(Page), MYF(MY_WME));
  this->pages = p;
}

void buf::BufPool::deinit_buffer_pool() {
  my_free(this->pages);
}

