//
// Created by lrf141 on 9/12/23.
//
#include <cinttypes>

#include "my_inttypes.h"
#include "my_sys.h"
#include "mysql/components/services/bits/my_io_bits.h"
#include "mysql/components/services/bits/psi_file_bits.h"

#include "file_handler.h"
#include "tablespace_type.h"

#ifndef TOYBOX_SYSTEM_TABLESPACE_H
#define TOYBOX_SYSTEM_TABLESPACE_H
namespace system_table {

constexpr const char *SYSTEM_TABLESPACE_PATH = "./toyboxsys";
constexpr const int SYSTEM_TABLESPACE_SIZE = 8;

// Error handling flag. See "my_sys.h".
constexpr const int MYF_STRICT_MODE = (MY_FAE | MY_WME);
constexpr const int MYF_THROUGH_ALL_ERRORS = 0;
constexpr const int MAX_TABLE_ID_INITIAL_VALUE = 0;

struct __attribute__ ((__packed__)) SystemTablespace {
  tablespace_id maxTablespaceId;
};

class SystemTablespaceImpl {
 private:
  SystemTablespace systemTablespace;
 public:
  SystemTablespaceImpl() : systemTablespace(SystemTablespace{0}) {}
  explicit SystemTablespaceImpl(tablespace_id tablespaceId)
      : systemTablespace(SystemTablespace{tablespaceId}) {}
  void incrementMaxTablespaceId();
  tablespace_id getMaxTablespaceId() const;
  uchar *toBinary();
};

class SystemTablespaceHandler {
 private:
  file_handler::File file;
  SystemTablespaceImpl systemTablespace;
 public:
  SystemTablespaceHandler();
  ~SystemTablespaceHandler() {}
  tablespace_id getNewMaxTablespaceId();
  static void create();
};
}

#endif  // TOYBOX_SYSTEM_TABLESPACE_H
