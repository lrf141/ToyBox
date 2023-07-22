#ifndef AVID_BUFFER_H
#define AVID_BUFFER_H

#include <stdlib.h>

#include "page.h"
#include "sql/psi_memory_key.h"

namespace buf {
class BufPool {
 private:
  Page *pages;
 public:
  void init_buffer_pool(PSI_memory_key buf, int bufPoolSize);
  void deinit_buffer_pool();
};
}

#endif  // MYSQL_BUFFER_H
