#include "system_table.h"

uint64_t SystemTableUseCaseImpl::getNewMaxTableId() {
  SystemTable systemTable = logic->get();
  uint64_t newMaxTableId = logic->updateMaxTableId(systemTable);
  return newMaxTableId;
}