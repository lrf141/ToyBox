//
// Created by lrf141 on 9/16/23.
//
#ifndef TOYBOX_TABLESPACE_H
#define TOYBOX_TABLESPACE_H

#include <cinttypes>

#include "file_handler.h"
#include "system_tablespace.h"

namespace tablespace {

constexpr const int TABLE_SPACE_START_POSITION = 0;
constexpr const int TABLE_SPACE_HEADER_START_POSITION
    = TABLE_SPACE_START_POSITION;
constexpr const int TABLE_SPACE_HEADER_SIZE = 16;
constexpr const int SYSTEM_PAGE_HEADER_START_POSITION =
    TABLE_SPACE_START_POSITION + TABLE_SPACE_HEADER_SIZE;
constexpr const int SYSTEM_PAGE_HEADER_SIZE = 16;
constexpr const int SYSTEM_PAGE_SIZE = 4096;
// TODO: replace to MySQL Column Max Size
constexpr const int COLUMN_NAME_MAX_SIZE = 64;
constexpr const int FIX_SIZE_COLUMN = 0;
constexpr const int VARIABLE_SIZE_COLUMN = 1;

constexpr const int SYSTEM_PAGE_ID = 0;

struct __attribute__ ((__packed__)) TablespaceHeader {
  uint64_t id;
  uint64_t pageCount;
};

class TablespaceHeaderImpl {
 private:
  TablespaceHeader tablespaceHeader{};
 public:
  TablespaceHeaderImpl() {}
  explicit TablespaceHeaderImpl(uint64_t tableId) {
    tablespaceHeader = TablespaceHeader{tableId, 0};
  }
  void read(file_handler::FileDescriptor fd);
  void flush(file_handler::FileDescriptor fd);
  void incrementPageCount();
  uint64_t getId();
  uint64_t getPageCount();
  uchar *toBinary();
};

struct __attribute__ ((__packed__)) SystemPageHeader {
  uint64_t pageId;
  uint64_t columnCount;
  uint8_t reserve[SYSTEM_PAGE_SIZE - SYSTEM_PAGE_HEADER_SIZE];
};

class SystemPageHeaderImpl {
 private:
  SystemPageHeader systemPageHeader;
 public:
  SystemPageHeaderImpl() : systemPageHeader(SystemPageHeader{}) {}
  void read(file_handler::FileDescriptor fd);
  void flush(file_handler::FileDescriptor fd);
  uchar *toBinary();
};

class TablespaceHandler {
 private:
  file_handler::File file;
  TablespaceHeaderImpl tablespaceHeader;
  SystemPageHeaderImpl systemPageHeader;
 public:
  TablespaceHandler(const char *path);
  ~TablespaceHandler() {}
  static file_handler::FileDescriptor create(const char *path, uint64_t tableId);
  TablespaceHeaderImpl getTablespaceHeader();
  SystemPageHeaderImpl getSystemPageHeader();
  file_handler::FileDescriptor getFileDescriptor();
};

}

#endif  // TOYBOX_TABLESPACE_H
