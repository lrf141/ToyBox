#include "system_table.h"

uint64_t SystemTableHandlerImpl::getNewMaxTableId() {
  return useCase->getNewMaxTableId();
}
