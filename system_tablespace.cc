//
// Created by lrf141 on 9/12/23.
//
#include "system_tablespace.h"
#include <fcntl.h>
#include <cassert>
#include <cstdlib>
#include <memory>

#include "file_util.h"

PSI_file_key system_tablespace_key;

namespace system_table {

File open() {
  return FileUtil::open(
      system_tablespace_key, SYSTEM_TABLESPACE_PATH, O_RDWR, MYF(0));
}

void close(File fd) {
  FileUtil::close(fd, MYF(0));
}

File create() {
  return FileUtil::create(
      system_tablespace_key, SYSTEM_TABLESPACE_PATH, 0, O_RDWR | O_TRUNC, MYF(0));
}

size_t read(File fd, uchar *buf) {
  FileUtil::seek(fd, 0, SEEK_SET, MYF(0));
  return FileUtil::read(fd, buf, SYSTEM_TABLESPACE_SIZE);
}

size_t write(File fd, uchar *buf) {
  FileUtil::seek(fd, 0, SEEK_SET, MYF(0));
  return FileUtil::write(fd, buf, SYSTEM_TABLESPACE_SIZE);
}

void init() {
  File fd = open();
  // if system_tablespace does not exist, create it file in initialize process.
  if (fd < 0) {
    close(fd);
    fd = create();
    std::unique_ptr<SystemTablespace> systemTablespace(new SystemTablespace);
    systemTablespace->maxTableId = 0;
    size_t writeSize = write(fd, reinterpret_cast<uchar *>(systemTablespace.get()));
    assert(writeSize);
  }
  close(fd);
}

SystemTablespaceDescriptor::SystemTablespaceDescriptor() {
  fd = open();
  uchar *buf = static_cast<uchar *>(calloc(SYSTEM_TABLESPACE_SIZE, sizeof(uchar)));
  size_t readSize = read(fd, buf);
  assert(readSize == SYSTEM_TABLESPACE_SIZE);
  systemTablespace = reinterpret_cast<SystemTablespace *>(buf);
}

SystemTablespaceDescriptor::~SystemTablespaceDescriptor() {
  delete systemTablespace;
  close(fd);
}

table_id SystemTablespaceDescriptor::getNewMaxTableId() {
  systemTablespace->maxTableId++;
  size_t writeSize = write(fd, reinterpret_cast<uchar *>(systemTablespace));
  assert(writeSize == SYSTEM_TABLESPACE_SIZE);
  return systemTablespace->maxTableId;
}

} // namespace system_table
