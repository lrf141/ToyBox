//
// Created by lrf141 on 9/13/23.
//
#include <gtest/gtest.h>
#include <iostream>
#include "system_tablespace.h"

class SystemTablespaceTest : public testing::Test {
 protected:
  system_table::SystemTablespaceHandler *sut;

  void SetUp() override {
    system_table::SystemTablespaceHandler::create();
    sut = new system_table::SystemTablespaceHandler;
  }

  void TearDown() override {
    delete sut;
    sut = nullptr;
    std::remove(SYSTEM_TABLESPACE_PATH);
  }
};

TEST_F(SystemTablespaceTest, getNewMaxTableId) {
  // Setup
  table_id newTableId = 1;

  // Exercise
  table_id result = sut->getNewMaxTableId();
  file_handler::File file;
  file.open(SYSTEM_TABLESPACE_PATH);
  system_table::SystemTablespace systemTablespace(0);
  size_t readSize = file.read(systemTablespace.toBinary(), SYSTEM_TABLESPACE_SIZE);

  // Verify
  ASSERT_EQ(result, newTableId);
  ASSERT_EQ(readSize, SYSTEM_TABLESPACE_SIZE);
  ASSERT_EQ(systemTablespace.getMaxTableId(), newTableId);
}
