//
// Created by lrf141 on 23/07/14.
//
#include "file_util.h"

#include <mysql/psi/mysql_file.h>


// tableFilePath = "./[database]/[table].[ext]
File FileUtil::create(PSI_file_key key, const char *tableFilePath, int srcLine, int createFlag, myf myfFlag) {
  return mysql_file_create(key, tableFilePath, srcLine, createFlag, myfFlag);
}

int FileUtil::close(File file, myf my_flags) {
  return mysql_file_close(file, my_flags);
}

File FileUtil::open(PSI_file_key key, const char *tableFilePath, int openFlag, myf flags) {
  return mysql_file_open(key, tableFilePath, openFlag, flags);
}

int FileUtil::remove(PSI_file_key key, const char *tableFilePath, myf flags) {
  return mysql_file_delete(key, tableFilePath, flags);
}

void FileUtil::convertToTableFilePath(char *tableFilePath, const char *name, const char *ext) {
  fn_format(tableFilePath, name, "", ext, MY_REPLACE_EXT | MY_UNPACK_FILENAME);
}

size_t FileUtil::read(File fd, uchar *buf, int readSize) {
  return mysql_file_read(fd, buf, readSize, MYF(0));
}

size_t FileUtil::write(File fd, uchar *buf, int writeSize) {
  return mysql_file_write(fd, buf, writeSize, MYF(0));
}

/**
 *
 * @param fd file descriptor
 * @param position wanna set position (byte)
 * @param whence SEEK_SET, SEEK_CUR, SEEK_END
 * @param flags myf
 */
void FileUtil::seek(File fd, my_off_t position, int whence, myf flags) {
  mysql_file_seek(fd, position, whence, flags);
}
