#ifndef TOYBOX_FILE_UTIL_H
#define TOYBOX_FILE_UTIL_H

#include "my_inttypes.h"
#include "mysql/components/services/bits/psi_file_bits.h"

class FileUtil
{
 public:
  static File create(PSI_file_key key, const char *tableFilePath, int srcLine, int createFlag, myf myfFlag);
  static int close(File file, myf flags);
  static int remove(PSI_file_key key, const char *tableFilePath, myf flags);
  static File open(PSI_file_key key, const char *tableFilePath, int openFlag, myf flags);
  static size_t read(File fd, uchar *buf, int readSize);
  static size_t write(File fd, uchar *buf, int writeSize);
  static void seek(File fd, my_off_t startPosition, int whence, myf flags);
  static void convertToTableFilePath(char *tableFilePath, const char *name, const char *ext);

 private:
  FileUtil() {}
  ~FileUtil() {}
};

#endif  // TOYBOX_FILE_UTIL_H
