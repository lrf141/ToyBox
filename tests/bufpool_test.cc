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
  uchar result[4];
  uint32_t readSize = 4; // byte
  int tupleCount = 1;
  std::cout << "Page Body Size: " << sizeof(page->body) << std::endl;

  // Initialize 4 bytes from the end
  for (int i = PAGE_BODY_SIZE - static_cast<int>(readSize); i < PAGE_BODY_SIZE; i++) {
    page->body[i] = 1;
  }
  int readPosition = PAGE_BODY_SIZE - (tupleCount * readSize);

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
