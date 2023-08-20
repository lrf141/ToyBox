#include "system_table.h"

uint64_t SystemTableUseCaseImpl::getNewMaxTableSpaceId() {
  SystemTable systemTable = logic->get();
  uint64_t newMaxTableId = logic->updateMaxTableSpaceId(systemTable);
  return newMaxTableId;
}