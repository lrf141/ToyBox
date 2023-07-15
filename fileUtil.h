#ifndef MYSQL_FILEUTIL_H
#define MYSQL_FILEUTIL_H

#include "my_inttypes.h"
#include "mysql/components/services/bits/psi_file_bits.h"

class FileUtil
{
 public:
  static File create(PSI_file_key key, const char *name, char *filePath, const char *fileExt, int srcLine, int createFlag, myf myfFlag);
  static int close(File file, myf flags);
  static int remove(PSI_file_key key, char *filePath, myf flags);

 private:
  FileUtil() {}
  ~FileUtil() {}
};

#endif  // MYSQL_FILEUTIL_H
