#include "file_util.h"
#include "my_sys.h"
#include "table_space_header.h"

size_t TableSpaceHeaderRepositoryImpl::write(TableSpaceHeader tableSpaceHeader, File fd, uint64_t position) {
  FileUtil::seek(fd, position, MY_SEEK_SET, MYF(0));
  return FileUtil::write(fd, (uchar *)&tableSpaceHeader, TABLE_SPACE_HEADER_SIZE);
}