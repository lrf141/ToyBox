#ifndef TOYBOX_TABLE_SPACE_H
#define TOYBOX_TABLE_SPACE_H

#include "table_space_header.h"
#include "mysql/components/services/bits/my_io_bits.h"

#define TABLE_SPACE_EXT ".tybx"
#define TABLE_SPACE_HEADER_START_POS 0
#define TABLE_SPACE_SYSTEM_PAGE_START_POS (TABLE_SPACE_HEADER_START_POS + TABLE_SPACE_HEADER_SIZE)

static PSI_file_key key_file_data;

struct TableSpace {
  TableSpaceHeader tableSpaceHeader;
};

class TableSpaceRepository {
 public:
  virtual ~TableSpaceRepository() = 0;
  virtual File create(const char *tableSpaceFileName) = 0;
  virtual int remove(const char *tableSpaceFilePath) = 0;
};

class TableSpaceRepositoryImpl : public TableSpaceRepository {
 public:
  ~TableSpaceRepositoryImpl() override {}
  File create(const char *tableSpaceFileName) override;
  int remove(const char *tableSpaceFilePath) override;
};

class TableSpaceLogic {
 public:
  virtual ~TableSpaceLogic() = 0;
  virtual File create(const char *tableSpaceFileName) = 0;
  virtual int truncate(const char *tableSpaceFilePath) = 0;
};

class TableSpaceLogicImpl : public TableSpaceLogic {
 private:
  TableSpaceRepository *repository;
 public:
  TableSpaceLogicImpl() : repository(new TableSpaceRepositoryImpl) {}
  ~TableSpaceLogicImpl() override {
    delete repository;
  }
  File create(const char *tableSpaceFileName) override;
  int truncate(const char *tableSpaceFilePath) override;
};

class TableSpaceUseCase {
 public:
  virtual ~TableSpaceUseCase() = 0;
  virtual int create(const char *tableSpaceFilePath, uint64_t tableSpaceId) = 0;
  virtual int truncate(const char *tableSpaceFilePath) = 0;
};

class TableSpaceUseCaseImpl : public TableSpaceUseCase {
 private:
  TableSpaceLogic *logic;
  TableSpaceHeaderLogic *tableSpaceHeaderLogic;
 public:
  TableSpaceUseCaseImpl() :
                            logic(new TableSpaceLogicImpl()),
                            tableSpaceHeaderLogic(new TableSpaceHeaderLogicImpl()) {}
  ~TableSpaceUseCaseImpl() override {
    delete tableSpaceHeaderLogic;
    delete logic;
  }
  int create(const char *tableSpaceFilePath, uint64_t tableSpaceId) override;
  int truncate(const char *tableSpaceFilePath) override;
};

class TableSpaceHandler {
 public:
  virtual ~TableSpaceHandler() = 0;
  virtual int createTable(const char *tableSpaceFilePath, uint64_t tableSpaceId, bool isTruncate) = 0;
};

class TableSpaceHandlerImpl : public TableSpaceHandler {
 private:
  TableSpaceUseCase *useCase;
 public:
  TableSpaceHandlerImpl() : useCase(new TableSpaceUseCaseImpl()) {}
  ~TableSpaceHandlerImpl() override {
    delete useCase;
  }
  int createTable(const char *tableSpaceFilePath, uint64_t tableSpaceId, bool isTruncate) override;
};

class TableSpaceHelper {
 public:
  static char *convertToTableFilePath(char *tableSpaceFilePath, const char *name);
};

#endif  // TOYBOX_TABLE_SPACE_H
