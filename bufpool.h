#ifndef AVID_BUFFER_H
#define AVID_BUFFER_H

#include <stdlib.h>

#include "table_file.h"
#include "page.h"
#include "sql/psi_memory_key.h"
#include "my_inttypes.h"

namespace buf {
class BufPool {
 private:
  void write_fixed_size_part(uchar *buf, uint32_t size, int position, int pageId);
  void read_fixed_size_part(uchar *buf, uint32_t size, int position, int pageId);
 public:
  Page *pages;
  void init_buffer_pool(PSI_memory_key buf, int bufPoolSize);
  void deinit_buffer_pool();
  void write(uchar *buf, uint32_t size, int position, int pageId);
  void read(uchar *buf, uint32_t size, int tupleId, int pageId);
  void flush(File fd);
};
}

#endif  // MYSQL_BUFFER_H
