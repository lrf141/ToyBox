#ifndef MYSQL_TABLE_FILE_H
#define MYSQL_TABLE_FILE_H

#include <mysql/psi/mysql_file.h>

class TableFileImpl {
 public:
   static int create(PSI_file_key key, const char *tableFilePath);
   static int truncate(PSI_file_key key, const char *tableFilePath);
   static File open(PSI_file_key key, const char *tableFilePath);
   static int remove(PSI_file_key key, const char *tableFilePath);
   static int close(File file);
};

#endif  // MYSQL_TABLE_FILE_H
