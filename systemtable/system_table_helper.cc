#include "system_table.h"
#include "file_util.h"
#include <fcntl.h>

File SystemTableHelper::open() {
  return FileUtil::open(key_file_system, SYSTEM_TABLE_PATH, O_RDWR, MYF(0));
}

File SystemTableHelper::create(File fd) {
  close(fd);
  File systemTableFile = FileUtil::create(key_file_system, SYSTEM_TABLE_PATH, 0, O_RDWR | O_TRUNC, MYF(0));
  SystemTable *systemTable = static_cast<SystemTable *>(malloc(sizeof(SystemTable)));
  systemTable->maxTableId = 0;
  FileUtil::write(systemTableFile, (uchar *)systemTable, SYSTEM_TABLE_SIZE);
  close(fd);
  free(systemTable);
  return 0;
}

void SystemTableHelper::close(File fd) {
  FileUtil::close(fd, MYF(0));
}
