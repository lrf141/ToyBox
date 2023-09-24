#include "table_file.h"
#include <iostream>
#include "file_util.h"
#include "page.h"
#include "toybox_errorno.h"

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
  uchar *buf = (uchar *)calloc(16, sizeof(uchar));
  TableSpaceHeader *tableSpaceHeader;
  FileUtil::seek(fd, 0, MY_SEEK_SET, MYF(0));
  size_t readSize = read(fd, buf, 16);
  assert(readSize == 16);
  tableSpaceHeader = (TableSpaceHeader *)buf;
  return tableSpaceHeader;
}

size_t TableFileImpl::writeTableSpaceHeader(File fd, TableSpaceHeader tableSpaceHeader) {
  uchar *buf = (uchar *)calloc(16, sizeof(uchar));
  buf = reinterpret_cast<uchar *>(&tableSpaceHeader);
  FileUtil::seek(fd, 0, MY_SEEK_SET, MYF(0));
  size_t wroteSize = write(fd, buf, 16);
  return wroteSize;
}

SystemPageHeader *TableFileImpl::readSystemPageHeader(File fd) {
  uchar *buf = (uchar *)calloc(16, sizeof(uchar));
  SystemPageHeader *systemPageHeader;
  FileUtil::seek(fd, 0 + 16, MY_SEEK_SET, MYF(0));
  size_t readSize = read(fd, buf, 16);
  assert(readSize == 16);
  systemPageHeader = (SystemPageHeader *)buf;
  return systemPageHeader;
}

size_t TableFileImpl::writeSystemPageHeader(File fd, SystemPageHeader systemPageHeader) {
  uchar *buf = (uchar *)calloc(16, sizeof(uchar));
  buf = reinterpret_cast<uchar *>(&systemPageHeader);
  FileUtil::seek(fd, 0 + 16, MY_SEEK_SET, MYF(0));
  size_t wroteSize = write(fd, buf, 16);
  return wroteSize;
}

size_t TableFileImpl::read(File fd, uchar *buf, int readSize) {
  return FileUtil::read(fd, buf, readSize);
}

size_t TableFileImpl::write(File fd, uchar *buf, int writeSize) {
  return FileUtil::write(fd, buf, writeSize);
}

size_t TableFileImpl::reserveSystemPage(File fd) {
  uchar *buf = (uchar *)calloc(4096, sizeof(uchar));
  FileUtil::seek(fd, 0 + 16, MY_SEEK_SET, MYF(0));
  size_t writeSize = write(fd, buf, 4096);
  free(buf);
  return writeSize;
}

size_t TableFileImpl::reservePage(File fd, int pageId) {
  uchar *buf = (uchar *)calloc(PAGE_SIZE, sizeof(uchar));
  my_off_t offset = 0 +
                    16 +
                    4096 + (PAGE_SIZE * pageId);
  FileUtil::seek(fd, offset, MY_SEEK_SET, MYF(0));
  size_t writeSize = write(fd, buf, PAGE_SIZE);
  free(buf);
  return writeSize;
}

Page *TableFileImpl::readPage(File fd, uint32_t pageId) {
  Page *page = (Page *)malloc(sizeof(Page));
  uchar *buf = (uchar *)calloc(PAGE_SIZE, sizeof(uchar));
  my_off_t offset = 0
                    + 16
                    + 4096 + (PAGE_SIZE * pageId);
  FileUtil::seek(fd, offset, MY_SEEK_SET, MYF(0));
  size_t readSize = read(fd, buf, PAGE_SIZE);
  assert(readSize == PAGE_SIZE);
  memcpy(page, buf, PAGE_SIZE);
  free(buf);
  return page;
}
