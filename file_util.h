#ifndef MYSQL_FILE_UTIL_H
#define MYSQL_FILE_UTIL_H

#include "my_inttypes.h"
#include "mysql/components/services/bits/psi_file_bits.h"

class FileUtil
{
 public:
  static File create(PSI_file_key key, const char *tableFilePath, int srcLine, int createFlag, myf myfFlag);
  static int close(File file, myf flags);
  static int remove(PSI_file_key key, const char *tableFilePath, myf flags);
  static void convertToTableFilePath(char *tableFilePath, const char *name, const char *ext);

 private:
  FileUtil() {}
  ~FileUtil() {}
};

#endif  // MYSQL_FILE_UTIL_H