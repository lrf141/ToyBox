
#include <gtest/gtest.h>
#include <iostream>
#include "system_tablespace.h"
#include "tablespace.h"

class TablespaceTest : public testing::Test {
 protected:
  tablespace::TablespaceHandler *sut;
  const char *path1 = "./hoge";
  const char *path2 = "./huga";

  void SetUp() override {
  }

  void TearDown() override {
    delete sut;
    sut = nullptr;
  }
};

TEST_F(TablespaceTest, createAndOpenTablespace) {
  // Setup & Exercise
  uint64_t tablespaceId = 1;
  tablespace::TablespaceHandler::create(path1, tablespaceId);
  sut = new tablespace::TablespaceHandler(path1);

  // Verify
  ASSERT_GT(sut->getFileDescriptor(), 0);
  ASSERT_EQ(sut->getTablespaceHeader().getId(), 1);
  ASSERT_EQ(sut->getTablespaceHeader().getPageCount(), 0);
}
