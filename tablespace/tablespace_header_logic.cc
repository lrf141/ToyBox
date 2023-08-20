#include "table_space.h"
#include <cassert>

TableSpaceHeader TableSpaceHeaderLogicImpl::create(uint64_t tableSpaceId) {
  return TableSpaceHeader{ tableSpaceId, 0 };
}

void TableSpaceHeaderLogicImpl::flush(TableSpaceHeader tableSpaceHeader, File fd, uint64_t position) {
  size_t writeSize = repository->write(tableSpaceHeader, fd, position);
  assert(writeSize == TABLE_SPACE_HEADER_SIZE);
}
