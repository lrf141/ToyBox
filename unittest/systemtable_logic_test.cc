#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "system_table.h"

class MockSystemTableRepository : public SystemTableRepository {
 public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(SystemTable, read, (File fd), (override));
  MOCK_METHOD(void, write, (File fd, SystemTable &systemTable), (override));
  MOCK_METHOD(int, close, (File fd), (override));
} *mockSystemTableRepository;

class SystemTableLogicImplTest : public testing::Test {
 protected:
  SystemTableLogicImpl *sut;

  void SetUp() override {
    mockSystemTableRepository = new MockSystemTableRepository();
    sut = new SystemTableLogicImpl(mockSystemTableRepository);
  }

  void TearDown() override {
    delete sut;
  }
};

TEST_F(SystemTableLogicImplTest, create) {
  // Exercise and Verify
  SystemTable  systemTable{0};
  ASSERT_EQ(systemTable.maxTableId, sut->create().maxTableId);
}

TEST_F(SystemTableLogicImplTest, updateMaxTableId) {
  // Setup
  SystemTable systemTable{0};
  File fakeFd = 0;
  EXPECT_CALL(*mockSystemTableRepository, open()).WillOnce(testing::Return(fakeFd));
  EXPECT_CALL(*mockSystemTableRepository, write(fakeFd, testing::_));
  EXPECT_CALL(*mockSystemTableRepository, close(testing::_));

  // Exercise
  uint64_t result = sut->updateMaxTableId(systemTable);

  // Verify
  ASSERT_EQ(result, 1);
}

TEST_F(SystemTableLogicImplTest, get) {
  // Setup
  SystemTable systemTable{123};
  File fakeFd = 0;
  EXPECT_CALL(*mockSystemTableRepository, open()).WillOnce(testing::Return(fakeFd));
  EXPECT_CALL(*mockSystemTableRepository, read(fakeFd)).WillOnce(testing::Return(systemTable));
  EXPECT_CALL(*mockSystemTableRepository, close(fakeFd));

  // Exercise
  SystemTable result = sut->get();

  // Verify
  ASSERT_EQ(result.maxTableId, systemTable.maxTableId);
}
