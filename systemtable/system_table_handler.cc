#include "system_table.h"

uint64_t SystemTableHandlerImpl::getNewMaxTableSpaceId() {
  return useCase->getNewMaxTableSpaceId();
}
