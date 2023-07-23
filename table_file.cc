#include "table_file.h"
#include "avid_errorno.h"
#include "file_util.h"
#include "page.h"

File TableFileImpl::create(PSI_file_key key, const char *tableFilePath) {
  File newTableFile;
  newTableFile = FileUtil::create(key, tableFilePath, 0, O_RDWR | O_TRUNC, MYF(0));
  if (newTableFile < 0) {
    return CANNOT_CREATE_TABLE_FILE;
  }
  return newTableFile;
}


File TableFileImpl::truncate(PSI_file_key key, const char *tableFilePath) {
  // TODO: reset SDI
  File newTableFile;
  int err = FileUtil::remove(key, tableFilePath, MYF(0));
  if (err < 0) {
    return CANNOT_DELETE_TABLE_FILE;
  }

  newTableFile = FileUtil::create(key, tableFilePath, 0, O_RDWR | O_TRUNC, MYF(0));
  if (newTableFile < 0) {
    return CANNOT_CREATE_TABLE_FILE;
  }

  return newTableFile;
}

File TableFileImpl::open(PSI_file_key key, const char *tableFilePath) {
  return mysql_file_open(key, tableFilePath, O_RDWR, MYF(0));
}

int TableFileImpl::remove(PSI_file_key key, const char *tableFilePath) {
  return FileUtil::remove(key, tableFilePath, MYF(0));
}

int TableFileImpl::close(File file) {
  return FileUtil::close(file, MYF(0));
}

TableSpaceHeader *TableFileImpl::readTableSpaceHeader(File fd) {
  uchar buf[TABLE_SPACE_HEADER_SIZE];
  TableSpaceHeader *tableSpaceHeader = (TableSpaceHeader *)malloc(sizeof(TableSpaceHeader));
  FileUtil::seek(fd, TABLE_SPACE_START_POSITION, MY_SEEK_SET, MYF(0));
  size_t readSize = read(fd, buf, TABLE_SPACE_HEADER_SIZE);
  assert(readSize == TABLE_SPACE_HEADER_SIZE);
  tableSpaceHeader = (TableSpaceHeader *)buf;
  return tableSpaceHeader;
}

size_t TableFileImpl::writeTableSpaceHeader(File fd, TableSpaceHeader tableSpaceHeader) {
  uchar *buf = (uchar *)malloc(sizeof(uchar) * TABLE_SPACE_HEADER_SIZE);
  buf = reinterpret_cast<uchar *>(&tableSpaceHeader);
  FileUtil::seek(fd, TABLE_SPACE_START_POSITION, MY_SEEK_SET, MYF(0));
  size_t wroteSize = write(fd, buf, TABLE_SPACE_HEADER_SIZE);
  return wroteSize;
}

SystemPageHeader *TableFileImpl::readSystemPageHeader(File fd) {
  uchar buf[TABLE_SPACE_HEADER_SIZE];
  SystemPageHeader *systemPageHeader = (SystemPageHeader *)malloc(sizeof(SystemPageHeader));
  FileUtil::seek(fd, TABLE_SPACE_START_POSITION + TABLE_SPACE_HEADER_SIZE, MY_SEEK_SET, MYF(0));
  size_t readSize = read(fd, buf, SYSTEM_PAGE_HEADER_SIZE);
  assert(readSize == SYSTEM_PAGE_HEADER_SIZE);
  systemPageHeader = (SystemPageHeader *)buf;
  return systemPageHeader;
}

size_t TableFileImpl::writeSystemPageHeader(File fd, SystemPageHeader systemPageHeader) {
  uchar *buf = (uchar *)malloc(sizeof(uchar) * SYSTEM_PAGE_HEADER_SIZE);
  buf = reinterpret_cast<uchar *>(&systemPageHeader);
  FileUtil::seek(fd, TABLE_SPACE_START_POSITION + TABLE_SPACE_HEADER_SIZE, MY_SEEK_SET, MYF(0));
  size_t wroteSize = write(fd, buf, SYSTEM_PAGE_HEADER_SIZE);
  return wroteSize;
}

ColumnInfo *TableFileImpl::readSystemPageColumnInfo(File fd, int index) {
  uchar buf[COLUMN_INFO_SIZE];
  int startPosition = TABLE_SPACE_START_POSITION + TABLE_SPACE_HEADER_SIZE + SYSTEM_PAGE_HEADER_SIZE;
  ColumnInfo *columnInfo = (ColumnInfo *)malloc(sizeof(ColumnInfo));
  FileUtil::seek(fd, startPosition + (COLUMN_INFO_SIZE * index), MY_SEEK_SET, MYF(0));
  size_t readSize = read(fd, buf, COLUMN_INFO_SIZE);
  assert(readSize == COLUMN_INFO_SIZE);
  columnInfo = (ColumnInfo *)buf;
  return columnInfo;
}

size_t TableFileImpl::read(File fd, uchar *buf, int readSize) {
  return FileUtil::read(fd, buf, readSize);
}

size_t TableFileImpl::writeSystemPageColumnInfo(File fd, ColumnInfo columnInfo, int index) {
  int startPosition = TABLE_SPACE_START_POSITION + TABLE_SPACE_HEADER_SIZE + SYSTEM_PAGE_HEADER_SIZE;
  uchar *buf = (uchar *)malloc(sizeof(uchar) * COLUMN_INFO_SIZE);
  buf = reinterpret_cast<uchar *>(&columnInfo);
  FileUtil::seek(fd, startPosition + (COLUMN_INFO_SIZE * index), MY_SEEK_SET, MYF(0));
  size_t wroteSize = write(fd, buf, COLUMN_INFO_SIZE);
  return wroteSize;
}

size_t TableFileImpl::write(File fd, uchar *buf, int writeSize) {
  return FileUtil::write(fd, buf, writeSize);
}

size_t TableFileImpl::reserveSystemPage(File fd) {
  uchar *buf = (uchar *)calloc(SYSTEM_PAGE_SIZE, sizeof(uchar));
  FileUtil::seek(fd, TABLE_SPACE_START_POSITION + TABLE_SPACE_HEADER_SIZE, MY_SEEK_SET, MYF(0));
  size_t writeSize = write(fd, buf, SYSTEM_PAGE_SIZE);
  free(buf);
  return writeSize;
}

size_t TableFileImpl::reservePage(File fd, int pageId) {
  uchar *buf = (uchar *)calloc(PAGE_SIZE, sizeof(uchar));
  my_off_t offset = TABLE_SPACE_START_POSITION + TABLE_SPACE_HEADER_SIZE + SYSTEM_PAGE_SIZE + (PAGE_SIZE * pageId);
  FileUtil::seek(fd, offset, MY_SEEK_SET, MYF(0));
  size_t writeSize = write(fd, buf, PAGE_SIZE);
  free(buf);
  return writeSize;
}
