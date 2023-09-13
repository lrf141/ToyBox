//
// Created by lrf141 on 9/12/23.
//

#include <cinttypes>

#include "my_inttypes.h"
#include "mysql/components/services/bits/my_io_bits.h"
#include "mysql/components/services/bits/psi_file_bits.h"

#ifndef TOYBOX_SYSTEM_TABLESPACE_H
#define TOYBOX_SYSTEM_TABLESPACE_H

#define SYSTEM_TABLESPACE_PATH "./toyboxsys"
#define SYSTEM_TABLESPACE_SIZE 8 // byte

typedef uint64_t table_id;

struct SystemTablespace {
  table_id maxTableId;
};

typedef struct SystemTablespace SystemTablespace;

namespace system_table {

File open();
void close(File fd);
File create();
size_t read(File fd);
size_t write(File fd, uchar *buf);
void init();

class SystemTablespaceDescriptor {
 private:
  SystemTablespace *systemTablespace;
  File fd;
 public:
  SystemTablespaceDescriptor();
  ~SystemTablespaceDescriptor();
  table_id getNewMaxTableId();
};
}

#endif  // TOYBOX_SYSTEM_TABLESPACE_H
