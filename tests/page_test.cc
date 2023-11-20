//
// Created by lrf141 on 9/26/23.
//
#include <gtest/gtest.h>
#include <memory>
#include "page.h"

class PageTest : public testing::Test {
 protected:
  page::PageHandler *sut;

  void SetUp() override {
    sut = new page::PageHandler(1);
  }

  void TearDown() override {
    delete sut;
    sut = nullptr;
  }
};

TEST_F(PageTest, insert) {
  // Setup
  std::unique_ptr<uint8_t> tupleBody(new uint8_t[]{1, 1, 1, 1, 1, 1, 1, 1});
  uint32_t tupleSize = 8;
  tuple::Tuple insertTuple = tuple::Tuple(tupleSize, 0, tupleBody.get());

  // Exercise
  sut->insert(insertTuple);

  // Verify
  ASSERT_EQ(sut->getPageHeader().freeBegin, 8);
  ASSERT_EQ(sut->getPageHeader().freeEnd, page::PAGE_BODY_SIZE - tupleSize);
  page::Slot insertedSlot = *reinterpret_cast<page::Slot *>(sut->getPageBody());
  ASSERT_EQ(insertedSlot.size, tupleSize);
  ASSERT_EQ(insertedSlot.recordStartOffset, page::PAGE_BODY_SIZE - tupleSize);
  for (int i = static_cast<int>(sut->getPageHeader().freeEnd);
       i < page::PAGE_BODY_SIZE; i++) {
    ASSERT_EQ(*(sut->getPageBody() + i), 1);
  }
}

TEST_F(PageTest, readTuple) {
  // Setup
  std::unique_ptr<uint8_t> tupleBody(new uint8_t[]{1, 1, 1, 1, 1, 1, 1, 1});
  uint32_t tupleSize = 8;
  tuple::Tuple insertTuple = tuple::Tuple(tupleSize, 0, tupleBody.get());
  sut->insert(insertTuple);

  // Exercise
  tuple::Tuple res = sut->readTuple(0);

  // Verify
  ASSERT_EQ(res.getSize(), 8);
  for (int i = 0; i < static_cast<int>(tupleSize); i++) {
    ASSERT_EQ(*(res.getData() + i), 1);
  }
}
