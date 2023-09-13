//
// Created by lrf141 on 9/13/23.
//
#include <gtest/gtest.h>
#include "system_tablespace.h"

class SystemTablespaceTest : public testing::Test {
 protected:
  system_table::SystemTablespaceHandler *sut;

  void SetUp() override {
    system_table::init();
    sut = new system_table::SystemTablespaceHandler;
  }

  void TearDown() override {
    delete sut;
    sut = nullptr;
    system_table::remove();
  }
};

TEST_F(SystemTablespaceTest, getNewMaxTableId) {
  // Setup
  table_id newTableId = 1;
  uchar *buf = static_cast<uchar *>(calloc(SYSTEM_TABLESPACE_SIZE, sizeof(uchar)));

  // Exercise
  table_id result = sut->getNewMaxTableId();
  File fd = system_table::open();
  size_t readSize = system_table::read(fd, buf);
  system_table::SystemTablespace *systemTablespace =
      reinterpret_cast<system_table::SystemTablespace *>(buf);

  // Verify
  ASSERT_EQ(result, newTableId);
  ASSERT_EQ(readSize, SYSTEM_TABLESPACE_SIZE);
  ASSERT_EQ(systemTablespace->maxTableId, newTableId);
}
