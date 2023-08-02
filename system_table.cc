#include "system_table.h"
#include <fcntl.h>
#include <cassert>
#include <cstdlib>

File SystemTableImpl::create(PSI_file_key key) {
  return FileUtil::create(key, SYSTEM_TABLE_PATH, 0, O_RDWR | O_TRUNC, MYF(0));
}

File SystemTableImpl::open(PSI_file_key key) {
  return FileUtil::open(key, SYSTEM_TABLE_PATH, O_RDWR, MYF(0));
}

SystemTable *SystemTableImpl::read(File fd) {
  uchar *buf = (uchar *)calloc(sizeof(uchar), MAX_PAGE_ID_SIZE);
  size_t readSize = FileUtil::read(fd, buf, MAX_PAGE_ID_SIZE);
  assert(readSize == MAX_PAGE_ID_SIZE);
  return (SystemTable *)buf;
}

size_t SystemTableImpl::write(File fd, uchar *buf) {
  FileUtil::seek(fd, 0, SEEK_SET, MYF(0));
  size_t writeSize = FileUtil::write(fd, buf, MAX_PAGE_ID_SIZE);
  assert(writeSize == MAX_PAGE_ID_SIZE);
  return writeSize;
}
int SystemTableImpl::close(File fd) {
  return FileUtil::close(fd, MYF(0));
}
