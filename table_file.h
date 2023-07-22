#ifndef MYSQL_TABLE_FILE_H
#define MYSQL_TABLE_FILE_H

#include <mysql/psi/mysql_file.h>

#include "file.h"

class TableFileImpl {
 public:
   static File create(PSI_file_key key, const char *tableFilePath);
   static File truncate(PSI_file_key key, const char *tableFilePath);
   static File open(PSI_file_key key, const char *tableFilePath);
   static int remove(PSI_file_key key, const char *tableFilePath);
   static size_t read(File fd, uchar *buf, int readSize);
   static size_t write(File fd, uchar *buf, int writeSize);
   static int close(File file);
   static TableSpaceHeader *readTableSpaceHeader(File fd);
   static size_t writeTableSpaceHeader(File fd, TableSpaceHeader tableSpaceHeader);
   static SystemPageHeader *readSystemPageHeader(File fd);
   static size_t writeSystemPageHeader(File fd, SystemPageHeader systemPageHeader);
   static ColumnInfo *readSystemPageColumnInfo(File fd);
   static size_t writeSystemPageColumnInfo(File fd, ColumnInfo columnInfo);
};

#endif  // MYSQL_TABLE_FILE_H
