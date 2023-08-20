#ifndef TOYBOX_TABLE_SPACE_HEADER_H
#define TOYBOX_TABLE_SPACE_HEADER_H

#include <cinttypes>
#include "mysql/components/services/bits/psi_file_bits.h"

#define TABLE_SPACE_HEADER_SIZE 16 // byte

struct TableSpaceHeader {
  uint64_t tableSpaceId;
  uint64_t pageCount;
};

typedef struct TableSpaceHeader TableSpaceHeader;

class TableSpaceHeaderRepository {
 public:
  virtual ~TableSpaceHeaderRepository() = 0;
  virtual size_t write(TableSpaceHeader tableSpaceHeader, File fd, uint64_t position) = 0;
};

class TableSpaceHeaderRepositoryImpl : public TableSpaceHeaderRepository{
 public:
  size_t write(TableSpaceHeader tableSpaceHeader, File fd, uint64_t position) override;
};

class TableSpaceHeaderLogic {
 public:
  virtual ~TableSpaceHeaderLogic() = 0;
  virtual TableSpaceHeader create(uint64_t tableSpaceId) = 0;
  virtual void flush(TableSpaceHeader tableSpaceHeader, File fd, uint64_t position) = 0;
};

class TableSpaceHeaderLogicImpl : public TableSpaceHeaderLogic {
 private:
  TableSpaceHeaderRepository *repository;
 public:
  TableSpaceHeaderLogicImpl() : repository(new TableSpaceHeaderRepositoryImpl()) {}
  ~TableSpaceHeaderLogicImpl() override {
    delete repository;
  }
  TableSpaceHeader create(uint64_t tableSpaceId) override;
  void flush(TableSpaceHeader tableSpaceHeader, File fd, uint64_t position) override;
};

#endif  // TOYBOX_TABLE_SPACE_HEADER_H
