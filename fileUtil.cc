//
// Created by lrf141 on 23/07/14.
//

#include "fileUtil.h"
#include "mysql/psi/mysql_file.h"

File FileUtil::create(const char *name, int create_flags,
                          int access_flags, myf my_flags) {
  return my_create(name, create_flags, access_flags, my_flags);
}

int FileUtil::close(File file, myf my_flags) {
  return my_close(file, my_flags);
}
