//
// Created by lrf141 on 9/16/23.
//
#ifndef TOYBOX_TABLESPACE_H
#define TOYBOX_TABLESPACE_H

#include <cinttypes>

namespace tablespace {

constexpr const int TABLE_SPACE_START_POSITION = 0;
constexpr const int TABLE_SPACE_HEADER_SIZE = 16;
constexpr const int SYSTEM_PAGE_HEADER_SIZE = 16;
constexpr const int SYSTEM_PAGE_SIZE = 4096;
// TODO: replace to MySQL Column Max Size
constexpr const int COLUMN_NAME_MAX_SIZE = 64;
constexpr const int FIX_SIZE_COLUMN = 0;
constexpr const int VARIABLE_SIZE_COLUMN = 1;

constexpr const int SYSTEM_PAGE_ID = 0;

class TablespaceHeader {
 private:
  uint64_t id;
  uint64_t pageCount;
};

class SystemPageHeader {
 private:
  uint64_t pageId;
  uint64_t columnCount;
};

class TablespaceHandler {

};

}

#endif  // TOYBOX_TABLESPACE_H
