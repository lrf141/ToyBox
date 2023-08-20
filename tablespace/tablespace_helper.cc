#include "my_sys.h"
#include "table_space.h"

char *TableSpaceHelper::convertToTableFilePath(char *tableSpaceFilePath, const char *name) {
  fn_format(
      tableSpaceFilePath,
      name,
      "",
      TABLE_SPACE_EXT,
      MY_REPLACE_EXT | MY_UNPACK_FILENAME
      );
  return tableSpaceFilePath;
}