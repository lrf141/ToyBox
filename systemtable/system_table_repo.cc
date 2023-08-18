#include <fcntl.h>
#include <cassert>
#include "file_util.h"
#include "system_table.h"

File SystemTableRepositoryImpl::open() {
  return FileUtil::open(key_file_system, SYSTEM_TABLE_PATH, O_RDWR, MYF(0));
}

SystemTable SystemTableRepositoryImpl::read(File fd) {
  uchar *buf = static_cast<uchar *>(calloc(sizeof(uchar), SYSTEM_TABLE_SIZE));
  size_t readSize = FileUtil::read(fd, buf, SYSTEM_TABLE_SIZE);
  SystemTable systemTable = *(SystemTable *)buf;
  assert(readSize == SYSTEM_TABLE_SIZE);
  free(buf);
  return systemTable;
}

void SystemTableRepositoryImpl::write(File fd, SystemTable &systemTable) {
  size_t writeSize = FileUtil::write(fd, (uchar *)&systemTable, SYSTEM_TABLE_SIZE);
  assert(writeSize == SYSTEM_TABLE_SIZE);
}

int SystemTableRepositoryImpl::close(File fd) {
  return FileUtil::close(fd, MYF(0));
}
