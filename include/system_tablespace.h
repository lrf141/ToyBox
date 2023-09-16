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

typedef uint64_t table_id;

namespace system_table {

constexpr const char *SYSTEM_TABLESPACE_PATH = "./toyboxsys";
constexpr const int SYSTEM_TABLESPACE_SIZE = 8;

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
  table_id getMaxTableId() const;
  uchar *toBinary();
};

class SystemTablespaceHandler {
 private:
  file_handler::File file;
  SystemTablespace systemTablespace;
 public:
  SystemTablespaceHandler();
  ~SystemTablespaceHandler() {}
  table_id getNewMaxTableId();
  static void create();
};
}

#endif  // TOYBOX_SYSTEM_TABLESPACE_H
