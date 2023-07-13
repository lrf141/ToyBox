#ifndef MYSQL_FILEUTIL_H
#define MYSQL_FILEUTIL_H

#include "my_inttypes.h"
#include "mysql/components/services/bits/my_io_bits.h"

class FileUtil
{
 public:
  static File create(const char *filename, int create_flags, int access_flags, myf flags);
  static int close(File file, myf flags);

 private:
  FileUtil() {}
  ~FileUtil() {}
};

#endif  // MYSQL_FILEUTIL_H
