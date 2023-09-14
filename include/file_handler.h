//
// Created by lrf141 on 9/14/23.
//
#ifndef TOYBOX_FILE_DESCRIPTOR_H
#define TOYBOX_FILE_DESCRIPTOR_H

#include "my_inttypes.h"
#include "mysql/components/services/bits/psi_file_bits.h"

namespace file_handler {

typedef int FileDescriptor;

class File {
 private:
  FileDescriptor fileDescriptor;
  myf myFlags;
  PSI_file_key fileKey;
 public:
  File() : fileDescriptor(-1), myFlags(0), fileKey(0) {}
  File(FileDescriptor fd, myf flags, PSI_file_key key)
      : fileDescriptor(fd),
        myFlags(flags),
        fileKey(key) {}
  File(const char *path, myf flags, PSI_file_key key)
      : myFlags(flags), fileKey(key) {
    open(path);
  }
  ~File() {
    if (fileDescriptor <= 0) {
      close();
    }
  }
  static File create(const char *path, PSI_file_key key);
  void open(const char *path);
  void close() const;
  size_t read(uchar *buf, int size) const;
  size_t write(uchar *buf, int size) const;
  FileDescriptor getFileDescriptor() {
    return fileDescriptor;
  }
};

} // namespace file_handler

#endif  // TOYBOX_FILE_DESCRIPTOR_H
