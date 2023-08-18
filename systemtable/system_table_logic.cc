#include "system_table.h"

SystemTable SystemTableLogicImpl::create() {
  static SystemTable systemTable;
  systemTable.maxTableId = 0;
  return systemTable;
}

uint64_t SystemTableLogicImpl::updateMaxTableId(SystemTable& systemTable) {
  systemTable.maxTableId++;
  File fd = repository->open();
  repository->write(fd, systemTable);
  repository->close(fd);
  return systemTable.maxTableId;
}

SystemTable SystemTableLogicImpl::get() {
  File fd = repository->open();
  SystemTable systemTable = repository->read(fd);
  repository->close(fd);
  return systemTable;
}
