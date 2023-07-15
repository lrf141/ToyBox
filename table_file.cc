#include "table_file.h"
#include "fileUtil.h"
#include "avid_errorno.h"

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
