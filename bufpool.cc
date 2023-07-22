#include "bufpool.h"
#include "my_sys.h"
#include "mysql/service_mysql_alloc.h"

void buf::BufPool::init_buffer_pool(PSI_memory_key b, int bufPoolSize) {
  Page *p = (Page *)my_malloc(b, bufPoolSize * sizeof(Page), MYF(MY_WME));
  //Page *p = (Page *)malloc(sizeof(Page) * bufPoolSize);
  this->pages = p;
}

void buf::BufPool::deinit_buffer_pool() {
  my_free(this->pages);
}

