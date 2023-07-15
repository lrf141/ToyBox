//
// Created by lrf141 on 23/07/14.
//
#include "fileUtil.h"

#include <mysql/psi/mysql_file.h>


File FileUtil::create(PSI_file_key key, const char *name, char *filePath, const char *fileExt, int srcLine,
                      int createFlag, myf myfFlag) {
  return mysql_file_create(key,
                           fn_format(
                               filePath, name, "", fileExt, MY_REPLACE_EXT | MY_UNPACK_FILENAME
                               ),
                           srcLine, createFlag, myfFlag);
}

int FileUtil::close(File file, myf my_flags) {
  return mysql_file_close(file, my_flags);
}

int FileUtil::remove(PSI_file_key key, char *filePath, myf flags) {
  return mysql_file_delete(key, filePath, flags);
}
