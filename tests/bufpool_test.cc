#include <gtest/gtest.h>
#include "bufpool.h"
#include "page.h"

class BufPoolTest : public testing::Test {
 protected:
  buf::BufPool *sut;
  Page *page;

  void SetUp() override {
    sut = new buf::BufPool();
    page = (Page *)calloc(PAGE_SIZE, sizeof(uchar));
    page->pageHeader.page_id = 0;
  }

  void TearDown() override {
    sut->deinit_buffer_pool();
    delete sut;
    free(page);

    sut = nullptr;
    page = nullptr;
  }
};

TEST_F(BufPoolTest, readFixedSizePart) {
  // Setup
  uint32_t readSize = 8; // byte
  uint8_t result[8];
  page->pageHeader.tupleCount = 1;
  // Initialize 8 bytes from the end
  for (int i = 0; i < static_cast<int>(readSize); i++) {
    page->body[PAGE_BODY_SIZE - (i + 1)] = 1;
  }
  int readPosition = PAGE_BODY_SIZE - (page->pageHeader.tupleCount * readSize);

  // Exercise
  sut->read_fixed_size_part(result, readSize, readPosition, page);

  // Verify
  int i = 0;
  for (; i < PAGE_BODY_SIZE - static_cast<int>(readSize); i++) {
    ASSERT_EQ(page->body[i], 0);
  }
  for (; i < PAGE_BODY_SIZE; i++) {
    ASSERT_EQ(page->body[i], 1);
  }
  for (i = 0; i < static_cast<int>(readSize); i++) {
    ASSERT_EQ(result[i], 1);
  }
}
