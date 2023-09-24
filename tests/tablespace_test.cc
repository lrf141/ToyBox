
#include "tablespace.h"
#include <gtest/gtest.h>
#include <filesystem>
#include <iostream>
#include "system_tablespace.h"

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
    if (std::filesystem::is_regular_file(path1)) {
      std::remove(path1);
    }
    if (std::filesystem::is_regular_file(path2)) {
      std::remove(path2);
    }
  }
};

TEST_F(TablespaceTest, createAndOpenTablespace) {
  // Setup
  uint64_t tablespaceId = 1;

  // Exercise
  tablespace::TablespaceHandler::create(path1, tablespaceId);

  // Verify
  sut = new tablespace::TablespaceHandler(path1);
  ASSERT_GT(sut->getFileDescriptor(), 0);
  ASSERT_EQ(sut->getTablespaceHeader().getId(), 1);
  ASSERT_EQ(sut->getTablespaceHeader().getPageCount(), 0);
}
