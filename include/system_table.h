#ifndef TOYBOX_SYSTEM_TABLE_H
#define TOYBOX_SYSTEM_TABLE_H

#include <cinttypes>
#include <string>
#include "my_inttypes.h"
#include "mysql/components/services/bits/psi_file_bits.h"

#define SYSTEM_TABLE_PATH "./toyboxsys"
#define SYSTEM_TABLE_SIZE 8 // byte

static PSI_file_key key_file_system;

struct SystemTable {
  uint64_t maxTableId;
};

typedef struct SystemTable SystemTable;

class SystemTableRepository {
 public:
  SystemTableRepository() {}
  virtual ~SystemTableRepository() {}
  virtual File open() = 0;
  virtual SystemTable read(File fd) = 0;
  virtual void write(File fd, SystemTable& systemTable) = 0;
  virtual int close(File fd) = 0;
};

class SystemTableRepositoryImpl : public SystemTableRepository {
 public:
  SystemTableRepositoryImpl() {}
  File open() override;
  SystemTable read(File fd) override;
  void write(File fd, SystemTable &systemTable) override;
  int close(File fd) override;
};

class SystemTableLogic {
 public:
  SystemTableLogic() {}
  virtual ~SystemTableLogic() {}
  virtual SystemTable create() = 0;
  virtual uint64_t updateMaxTableId(SystemTable& systemTable) = 0;
  virtual SystemTable get() = 0;
};

class SystemTableLogicImpl : public SystemTableLogic {
 private:
  SystemTableRepository *repository;
 public:
  SystemTableLogicImpl() : repository(new SystemTableRepositoryImpl()) {}
  // For Test
  SystemTableLogicImpl(SystemTableRepository *systemTableRepository) : repository(systemTableRepository) {}
  ~SystemTableLogicImpl() override {
    delete repository;
  }
  SystemTable create() override;
  uint64_t updateMaxTableId(SystemTable& systemTable) override;
  SystemTable get() override;
};

class SystemTableUseCase {
 public:
  SystemTableUseCase() {}
  virtual ~SystemTableUseCase() {}
  virtual uint64_t getNewMaxTableId() = 0;
};

class SystemTableUseCaseImpl : public SystemTableUseCase {
 private:
  SystemTableLogic *logic;
 public:
  SystemTableUseCaseImpl() : logic(new SystemTableLogicImpl()) {
  }
  ~SystemTableUseCaseImpl() {
    delete logic;
  }
  uint64_t getNewMaxTableId() override;
};

class SystemTableHandler {
 public:
  virtual uint64_t getNewMaxTableId() = 0;
};

class SystemTableHandlerImpl : public SystemTableHandler {
 private:
  SystemTableUseCase *useCase;
 public:
  SystemTableHandlerImpl() : useCase(new SystemTableUseCaseImpl) {
  }
  uint64_t getNewMaxTableId() override;
};

class SystemTableHelper {
 public:
  static File open();
  static File create(File fd);
  static void close(File fd);
};

#endif  // TOYBOX_SYSTEM_TABLE_H
