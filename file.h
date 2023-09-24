#ifndef TOYBOX_FILE_H
#define TOYBOX_FILE_H

#include <stdint.h>
#include "my_inttypes.h"

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

#endif  // TOYBOX_FILE_H
