#ifndef MYSQL_SYSTEM_TABLE_H
#define MYSQL_SYSTEM_TABLE_H

#define SYSTEM_TABLE_PATH "./avidsys"
// 8byte
#define MAX_PAGE_ID_SIZE 8

#include "file_util.h"

struct SystemTable {
  uint64_t maxTableId;
};

typedef struct SystemTable SystemTable;

class SystemTableImpl {
 public:
  static File create(PSI_file_key key);
  static File open(PSI_file_key key);
  static SystemTable *read(File fd);
  static size_t write(File fd, uchar *buf);
  static int close(File fd);
};

#endif  // MYSQL_SYSTEM_TABLE_H
