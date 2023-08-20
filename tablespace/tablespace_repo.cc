#include "table_space.h"
#include "file_util.h"
#include <fcntl.h>

File TableSpaceRepositoryImpl::create(const char *tableSpaceFileName) {
  return FileUtil::create(key_file_data, tableSpaceFileName, 0, O_RDWR | O_TRUNC, MYF(0));
}

int TableSpaceRepositoryImpl::remove(const char *tableSpaceFilePath) {
  return FileUtil::remove(0, tableSpaceFilePath, MYF(0));
}
