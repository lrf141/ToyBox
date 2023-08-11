#ifndef AVID_FILE_H
#define AVID_FILE_H

#include <stdint.h>
#include "my_inttypes.h"

#define TABLE_SPACE_START_POSITION 0
#define TABLE_SPACE_HEADER_SIZE 16
#define SYSTEM_PAGE_HEADER_SIZE 16
#define SYSTEM_PAGE_SIZE 4096
// TODO: replace to MySQL Column Max Size
#define COLUMN_NAME_MAX_SIZE 64
#define FIX_SIZE_COLUMN 0
#define VARIABLE_SIZE_COLUMN 1

#define SYSTEM_PAGE_ID 0

struct TableSpaceHeader {
  uint64_t tableSpaceId;
  uint64_t pageCount;
};

typedef struct TableSpaceHeader TableSpaceHeader;

struct SystemPageHeader {
  uint64_t pageId;
  uint64_t columnCount;
};

typedef struct SystemPageHeader SystemPageHeader;

#endif  // AVID_FILE_H
