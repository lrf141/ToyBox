//
// Created by lrf141 on 9/16/23.
//
#include "file_handler.h"
#include <gtest/gtest.h>
#include <iostream>
#include "mysql/psi/mysql_file.h"
#include "template_utils.h"

namespace {
PSI_file_key file_key_for_test;
PSI_file_info test_files[] = {
    {&file_key_for_test, "test", 0, 0, PSI_DOCUMENT_ME}
};

void init_test_keys() {
  const char *category = "unittest";
  int count = static_cast<int>(array_elements(test_files));
  mysql_file_register(category, test_files, count);
}
} // namespace

class FileHandlerTest : public testing::Test {
 protected:
  file_handler::File *sut;

  void SetUp() override {
    sut = new file_handler::File();
    init_test_keys();
  }

  void TearDown() override {
    delete sut;
    sut = nullptr;
  }
};

TEST_F(FileHandlerTest, createAndOpenTest) {
  // Setup
  const char *path = "./dummy1";
  file_handler::File::create(path, file_key_for_test);

  // Exercise
  sut->open(path);

  // Verify
  ASSERT_GT(sut->getFileDescriptor(), -1);

  // Clean up
  std::remove(path);
}

TEST_F(FileHandlerTest, readAndWriteTest) {
  // Setup
  const char *path = "./dummy2";
  file_handler::File sut = file_handler::File::create(path, file_key_for_test);
  uint64_t writeValue = 1;
  uint64_t readValue = 0;
  int valueSize = 8;

  // Exercise
  size_t writeSize = sut.write(reinterpret_cast<uchar *>(&writeValue), valueSize);
  size_t readSize = sut.read(reinterpret_cast<uchar *>(&readValue), valueSize);

  // Verify
  ASSERT_EQ(readValue, 1);
  ASSERT_EQ(readValue, writeValue);
  ASSERT_EQ(writeSize, valueSize);
  ASSERT_EQ(readSize, valueSize);

  // Clean up
  std::remove(path);
}