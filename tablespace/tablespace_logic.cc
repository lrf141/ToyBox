#include "table_space.h"

File TableSpaceLogicImpl::create(const char *tableSpaceFileName) {
  return repository->create(tableSpaceFileName);
}

int TableSpaceLogicImpl::truncate(const char *tableSpaceFilePath) {
  return repository->remove(tableSpaceFilePath);
}
