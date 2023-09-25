//
// Created by lrf141 on 9/14/23.
//
#include "file_handler.h"
#include <fcntl.h>

#include "file_util.h"
#include "file_config.h"

namespace file_handler {

void File::open(const char *path) {
  fileDescriptor = FileUtil::open(fileKey, path, O_RDWR, MYF(myFlags));
}

void File::remove(const char *path) {
  FileUtil::remove(fileKey, path, MYF(file_config::MYF_STRICT_MODE));
}

void File::close() const {
  FileUtil::close(fileDescriptor, MYF(myFlags));
}

File File::create(const char *path, PSI_file_key key) {
  FileDescriptor fd = FileUtil::create(
      key, path, 0, O_RDWR, MYF(0));
  return File(fd, 0, key);
}

size_t File::read(uchar *buf, int size) const {
  FileUtil::seek(fileDescriptor, 0, SEEK_SET, MYF(0));
  return FileUtil::read(fileDescriptor, buf, size);
}

size_t File::read(uchar *buf, int size, my_off_t offset) const {
  FileUtil::seek(fileDescriptor, offset, SEEK_SET, MYF(0));
  return FileUtil::read(fileDescriptor, buf, size);
}

size_t File::write(uchar *buf, int size) const {
  FileUtil::seek(fileDescriptor, 0, SEEK_SET, MYF(0));
  return FileUtil::write(fileDescriptor, buf, size);
}

size_t File::write(uchar *buf, int size, my_off_t offset) const {
  FileUtil::seek(fileDescriptor, offset, SEEK_SET, MYF(0));
  return FileUtil::write(fileDescriptor, buf, size);
}

} // namespace file_handler
