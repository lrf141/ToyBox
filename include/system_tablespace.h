//
// Created by lrf141 on 9/12/23.
//

#include <cinttypes>

#include "my_inttypes.h"
#include "my_sys.h"
#include "mysql/components/services/bits/my_io_bits.h"
#include "mysql/components/services/bits/psi_file_bits.h"

#ifndef TOYBOX_SYSTEM_TABLESPACE_H
#define TOYBOX_SYSTEM_TABLESPACE_H

#define SYSTEM_TABLESPACE_PATH "./toyboxsys"
#define SYSTEM_TABLESPACE_SIZE 8 // byte

typedef uint64_t table_id;

namespace system_table {

// Error handling flag. See "my_sys.h".
constexpr const int MYF_STRICT_MODE = (MY_FAE | MY_WME);
constexpr const int MYF_THROUGH_ALL_ERRORS = 0;

class SystemTablespace {
 private:
  table_id maxTableId;
 public:
  SystemTablespace(table_id tableId);
  void incrementMaxTableId();
  table_id getMaxTableId();
};

File open(myf flag);
void close(File fd);
File create();
size_t read(File fd, uchar *buf);
size_t write(File fd, uchar *buf);
void init();

class SystemTablespaceHandler {
 private:
  SystemTablespace *systemTablespace;
  File fd;
 public:
  SystemTablespaceHandler();
  ~SystemTablespaceHandler();
  table_id getNewMaxTableId();
};
}

#endif  // TOYBOX_SYSTEM_TABLESPACE_H
