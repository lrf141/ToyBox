#include <cassert>
#include "table_space.h"
#include "table_space_header.h"

int TableSpaceUseCaseImpl::create(const char *tableSpaceFilePath, uint64_t tableSpaceId) {
  File fd = logic->create(tableSpaceFilePath);
  assert(fd > 0);
  TableSpaceHeader tableSpaceHeader = tableSpaceHeaderLogic->create(tableSpaceId);

  return 0;
}

int TableSpaceUseCaseImpl::truncate(const char *tableSpaceFilePath) {
  return logic->truncate(tableSpaceFilePath);
}