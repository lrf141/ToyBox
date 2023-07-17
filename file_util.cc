//
// Created by lrf141 on 23/07/14.
//
#include "file_util.h"

#include <mysql/psi/mysql_file.h>


File FileUtil::create(PSI_file_key key, const char *tableFilePath, int srcLine, int createFlag, myf myfFlag) {
  return mysql_file_create(key, tableFilePath, srcLine, createFlag, myfFlag);
}

int FileUtil::close(File file, myf my_flags) {
  return mysql_file_close(file, my_flags);
}

int FileUtil::remove(PSI_file_key key, const char *tableFilePath, myf flags) {
  return mysql_file_delete(key, tableFilePath, flags);
}

void FileUtil::convertToTableFilePath(char *tableFilePath, const char *name, const char *ext) {
  fn_format(tableFilePath, name, "", ext, MY_REPLACE_EXT | MY_UNPACK_FILENAME);
}