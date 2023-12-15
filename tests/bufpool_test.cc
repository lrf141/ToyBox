#include <gtest/gtest.h>
#include "bufpool.h"
#include "page.h"

class BufPoolTest : public testing::Test {
 protected:
  buf::BufPool *sut;

  void SetUp() override {
    sut = new buf::BufPool();
  }

  void TearDown() override {
    sut->deinit_buffer_pool();
    delete sut;
    sut = nullptr;
  }
};

TEST_F(BufPoolTest, isLastPage) {
  // Setup
  tablespace_id tablespaceId = 1;
  page_id pageId = 1;
  page::PageHandler pageHandler = page::PageHandler(pageId);
  sut->elements = new buf::Element(tablespaceId, pageHandler);

  // Exercise
  bool isLastPage = sut->isLastPage(tablespaceId, pageId, "hoge");

  // Verify
  ASSERT_TRUE(isLastPage);
}

TEST_F(BufPoolTest, isLastPageWithMorePages) {
  // Setup
  tablespace_id tablespaceId = 1;
  page_id pageId = 1;
  page::PageHandler pageHandler = page::PageHandler(pageId);
  sut->elements = new buf::Element(tablespaceId, pageHandler);

  page::PageHandler page = page::PageHandler(pageId + 1);
  buf::Element *lastElement = new buf::Element(tablespaceId + 1, page);
  sut->elements->next = lastElement;

  // Exercise
  bool isLastPage = sut->isLastPage(tablespaceId + 1, pageId + 1, "dummy");

  // Verify
  ASSERT_TRUE(isLastPage);
}

TEST_F(BufPoolTest, isLastTuple) {
  // Setup
  tablespace_id tablespaceId = 1;
  page_id pageId = 1;
  uint64_t tupleId = 1;
  uint8_t buf[] = {1, 1, 1, 1};
  tuple::Tuple insertTuple{4, 0, buf};
  page::PageHandler pageHandler = page::PageHandler(pageId);
  pageHandler.getPageHeader().tupleCount = 1;
  pageHandler.insert(insertTuple);
  sut->elements = new buf::Element(tablespaceId, pageHandler);

  // Exercise
  bool isLastTuple = sut->isLastTuple(tablespaceId, pageId, tupleId, "hoge");

  // Verify
  ASSERT_TRUE(isLastTuple);
}

TEST_F(BufPoolTest, getElementWithEmptyElements) {
  // Exercise
  buf::Element *element = sut->getElement(1, 1);

  // Verify
  ASSERT_EQ(element, nullptr);
}

TEST_F(BufPoolTest, getElement) {
  // Setup
  tablespace_id tablespaceId = 1;
  page_id pageId = 1;
  uint64_t tupleId = 1;
  page::PageHandler pageHandler = page::PageHandler(pageId);
  pageHandler.getPageHeader().tupleCount = tupleId;
  sut->elements = new buf::Element(tablespaceId, pageHandler);

  // Exercise
  buf::Element *element = sut->getElement(tablespaceId, pageId);

  // Verify
  ASSERT_NE(element, nullptr);
  ASSERT_EQ(element->next, nullptr);
  ASSERT_EQ(element->tableSpaceId, tablespaceId);
  ASSERT_EQ(element->refCount, 0);
  ASSERT_EQ(element->getPageHandler().getPageHeader().id, pageId);
}

TEST_F(BufPoolTest, existPageWithEmptyElements) {
  // Exercise
  bool existPage = sut->existPage(1, 1);

  // Verify
  ASSERT_FALSE(existPage);
}

TEST_F(BufPoolTest, existPage) {
  // Setup
  tablespace_id tablespaceId = 1;
  page_id pageId = 1;
  uint64_t tupleId = 1;
  page::PageHandler pageHandler = page::PageHandler(pageId);
  pageHandler.getPageHeader().tupleCount = tupleId;
  sut->elements = new buf::Element(tablespaceId, pageHandler);

  // Exercise
  bool existPage = sut->existPage(tablespaceId, pageId);
  bool existPageNoMatchTablespaceId = sut->existPage(tablespaceId + 1, pageId);
  bool existPageNoMatchPageId = sut->existPage(tablespaceId, pageId + 1);

  // Verify
  ASSERT_TRUE(existPage);
  ASSERT_FALSE(existPageNoMatchTablespaceId);
  ASSERT_FALSE(existPageNoMatchPageId);
}

TEST_F(BufPoolTest, write) {
  // Setup
  tablespace_id tablespaceId = 1;
  page_id pageId = 1;
  uchar buf[] = {1, 1, 1, 1};
  char tablespacePath[] = "dummy";
  tuple::Tuple *newTuple = new tuple::Tuple(4, 0, buf);
  page::PageHandler pageHandler = page::PageHandler(pageId);
  sut->elements = new buf::Element(tablespaceId, pageHandler);
  buf::WriteDescriptor writeDescriptor{tablespaceId, pageId, tablespacePath, newTuple};

  // Exercise
  sut->write(buf, writeDescriptor);

  // Verify
  page::Header header = sut->elements->getPageHandler().getPageHeader();
  ASSERT_EQ(header.tupleCount, 1);
  ASSERT_EQ(header.freeBegin, page::SLOT_SIZE);
  ASSERT_EQ(header.freeEnd, page::PAGE_BODY_SIZE - 4);
}

TEST_F(BufPoolTest, writeAndRead) {
  // Setup
  tablespace_id tablespaceId = 1;
  page_id pageId = 1;
  uint64_t tupleId = 0;
  uchar buf[] = {1, 1, 1, 1};
  uchar readBuf[] = {0, 0, 0, 0};
  char tablespacePath[] = "dummy";
  tuple::Tuple *newTuple = new tuple::Tuple(4, 0, buf);
  page::PageHandler pageHandler = page::PageHandler(pageId);
  sut->elements = new buf::Element(tablespaceId, pageHandler);
  buf::WriteDescriptor writeDescriptor{tablespaceId, pageId, tablespacePath, newTuple};
  buf::ReadDescriptor readDescriptor{tablespaceId, pageId, tupleId, tablespacePath};

  // Exercise
  sut->write(buf, writeDescriptor);
  int readSize = sut->read(readBuf, readDescriptor);

  // Verify
  page::Header header = sut->elements->getPageHandler().getPageHeader();
  ASSERT_EQ(header.tupleCount, 1);
  ASSERT_EQ(header.freeBegin, page::SLOT_SIZE);
  ASSERT_EQ(header.freeEnd, page::PAGE_BODY_SIZE - 4);
  ASSERT_EQ(readSize, 4);
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(readBuf[i], 1);
  }
}
