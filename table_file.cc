#include "table_file.h"
#include "avid_errorno.h"
#include "fileUtil.h"
#include "my_io.h"

int TableFileImpl::create(PSI_file_key key, const char *name, char *filePath) {
  File tableFile;
  tableFile = FileUtil::create(key, name, filePath, ".json", 0, O_RDWR | O_TRUNC, MYF(0));
  if (tableFile < 0) {
    return CANNOT_CREATE_TABLE_FILE;
  }

  int err = FileUtil::close(tableFile, MYF(0));
  if (err < 0) {
    return CANNOT_CLOSE_TABLE_FILE;
  }

  return 0;
}


int TableFileImpl::truncate(PSI_file_key key, const char *name, char *filePath) {
  // TODO: reset SDI
  File newTableFile;
  int err = FileUtil::remove(key, filePath, MYF(0));
  if (err < 0) {
    return CANNOT_DELETE_TABLE_FILE;
  }

  newTableFile = FileUtil::create(key, name, filePath, ".json", 0, O_RDWR | O_TRUNC, MYF(0));
  if (newTableFile < 0) {
    return CANNOT_CREATE_TABLE_FILE;
  }

  err = FileUtil::close(newTableFile, MYF(0));
  if (err < 0) {
    return CANNOT_CLOSE_TABLE_FILE;
  }

  return 0;
}
File TableFileImpl::open(PSI_file_key key, const char *filePath) {
  return mysql_file_open(key, filePath, O_RDWR, MYF(0));
}

int TableFileImpl::remove(PSI_file_key key, const char *filePath) {
  char tableFilePath[FN_REFLEN];
  fn_format(
                 tableFilePath, filePath, "", ".json", MY_REPLACE_EXT | MY_UNPACK_FILENAME
                 );
  return FileUtil::remove(key, tableFilePath, MYF(0));
}

int TableFileImpl::close(File file) {
  return FileUtil::close(file, MYF(0));
}
