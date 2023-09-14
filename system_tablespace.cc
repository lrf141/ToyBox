//
// Created by lrf141 on 9/12/23.
//
#include "system_tablespace.h"
#include <fcntl.h>
#include <cassert>
#include <memory>

#include "file_util.h"

PSI_file_key system_tablespace_key;

namespace system_table {

void SystemTablespace::incrementMaxTableId() {
  maxTableId++;
}

table_id SystemTablespace::getMaxTableId() {
  return maxTableId;
}

uchar *SystemTablespace::toBinary() {
  return reinterpret_cast<uchar *>(this);
}

File open(myf flag) {
  return FileUtil::open(
      system_tablespace_key, SYSTEM_TABLESPACE_PATH, O_RDWR, MYF(flag));
}

void close(File fd) {
  FileUtil::close(fd, MYF(MYF_STRICT_MODE));
}

File create() {
  return FileUtil::create(
      system_tablespace_key, SYSTEM_TABLESPACE_PATH, 0, O_RDWR | O_TRUNC, MYF(MYF_STRICT_MODE));
}

size_t read(File fd, uchar *buf) {
  FileUtil::seek(fd, 0, SEEK_SET, MYF(MYF_STRICT_MODE));
  return FileUtil::read(fd, buf, SYSTEM_TABLESPACE_SIZE);
}

size_t write(File fd, uchar *buf) {
  FileUtil::seek(fd, 0, SEEK_SET, MYF(MYF_STRICT_MODE));
  return FileUtil::write(fd, buf, SYSTEM_TABLESPACE_SIZE);
}

void init() {
  File fd = open(MYF_THROUGH_ALL_ERRORS);
  // if system_tablespace does not exist, create it file in initialize process.
  if (fd < 0) {
    fd = create();
    std::unique_ptr<SystemTablespace> systemTablespace(
        new SystemTablespace(MAX_TABLE_ID_INITIAL_VALUE)
        );
    size_t writeSize = write(fd, reinterpret_cast<uchar *>(systemTablespace.get()));
    assert(writeSize);
  }
  close(fd);
}

SystemTablespaceHandler::SystemTablespaceHandler() {
  file = file_handler::File(SYSTEM_TABLESPACE_PATH, MYF_STRICT_MODE, system_tablespace_key);
  SystemTablespace *temp = new SystemTablespace;
  size_t readSize = file.read(temp->toBinary(), SYSTEM_TABLESPACE_SIZE);
  assert(readSize == SYSTEM_TABLESPACE_SIZE);
  systemTablespace = temp;
}

table_id SystemTablespaceHandler::getNewMaxTableId() {
  systemTablespace->incrementMaxTableId();
  size_t writeSize = file.write(systemTablespace->toBinary(), SYSTEM_TABLESPACE_SIZE);
  assert(writeSize == SYSTEM_TABLESPACE_SIZE);
  return systemTablespace->getMaxTableId();
}

} // namespace system_table
