#include "table_space.h"

int TableSpaceHandlerImpl::createTable(const char *tableSpaceFilePath, uint64_t tableSpaceId, bool isTruncate) {
  if (isTruncate) {
    // Do truncate table
    int err = useCase->truncate(tableSpaceFilePath);
    return err;
  }
  return useCase->create(tableSpaceFilePath, tableSpaceId);
}