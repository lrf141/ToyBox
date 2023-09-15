//
// Created by lrf141 on 9/12/23.
//
#include <cinttypes>

#include "my_inttypes.h"
#include "my_sys.h"
#include "mysql/components/services/bits/my_io_bits.h"
#include "mysql/components/services/bits/psi_file_bits.h"

#include "file_handler.h"

#ifndef TOYBOX_SYSTEM_TABLESPACE_H
#define TOYBOX_SYSTEM_TABLESPACE_H

#define SYSTEM_TABLESPACE_PATH "./toyboxsys"
#define SYSTEM_TABLESPACE_SIZE 8 // byte

typedef uint64_t table_id;

namespace system_table {

// Error handling flag. See "my_sys.h".
constexpr const int MYF_STRICT_MODE = (MY_FAE | MY_WME);
constexpr const int MYF_THROUGH_ALL_ERRORS = 0;
constexpr const int MAX_TABLE_ID_INITIAL_VALUE = 0;

class SystemTablespace {
 private:
  table_id maxTableId;
 public:
  SystemTablespace() : maxTableId(0) {}
  explicit SystemTablespace(table_id tableId) : maxTableId(tableId) {}
  void incrementMaxTableId();
  table_id getMaxTableId();
  uchar *toBinary();
};

File open(myf flag);
void close(File fd);
File create();
size_t read(File fd, uchar *buf);
size_t write(File fd, uchar *buf);
void init();

class SystemTablespaceHandler {
 private:
  file_handler::File file;
  SystemTablespace *systemTablespace;
 public:
  SystemTablespaceHandler();
  ~SystemTablespaceHandler() {
    delete systemTablespace;
  }
  table_id getNewMaxTableId();
};
}

#endif  // TOYBOX_SYSTEM_TABLESPACE_H
