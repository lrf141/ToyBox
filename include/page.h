//
// Created by lrf141 on 9/25/23.
//
#ifndef TOYBOX_PAGE_H
#define TOYBOX_PAGE_H

#include <cinttypes>

#include "file_handler.h"
#include "tablespace.h"
#include "page_type.h"

namespace page {

constexpr const int PAGE_HEADER_SIZE = 24;
constexpr const int PAGE_SIZE = 4096;
constexpr const int PAGE_BODY_SIZE = PAGE_SIZE - PAGE_HEADER_SIZE;
constexpr const int PAGE_START_POSITION = tablespace::TABLE_SPACE_START_POSITION +
                                          tablespace::TABLE_SPACE_HEADER_SIZE +
                                          tablespace::SYSTEM_PAGE_SIZE;
constexpr const page_id MAX_PAGE_ID = UINT64_MAX;

struct __attribute__ ((__packed__)) Header {
  page_id id;
  tuple_size tupleCount;
  page_id nextPageId;
};

struct __attribute__ ((__packed__)) Page {
  Header header;
  uint8_t body[PAGE_BODY_SIZE];
};

class PageImpl {
 private:
  Page page;
 public:
  explicit PageImpl(page_id pageId) : page(Page{Header{pageId, 0, MAX_PAGE_ID}, {0}}) {}
  uint8_t *toBinary() {
    return reinterpret_cast<uint8_t *>(&page);
  }

  page_id getPageId() const {
    return page.header.id;
  }

  page_id getNextPageId() const {
    return page.header.nextPageId;
  }

  Header& getHeader() {
    return page.header;
  }

  void incrementTupleCount() {
    page.header.tupleCount++;
  }

  Page& getPage() {
    return page;
  }
};

class PageHandler {
 private:
  PageImpl page;
 public:
  explicit PageHandler(page_id pageId) : page(PageImpl(pageId)) {}
  static PageHandler reserveNewPage(page_id maxPageId);
  void flush(file_handler::FileDescriptor fd);
  void read(file_handler::FileDescriptor fd);
  PageImpl& getPage() {
    return page;
  }
  uchar *getPageBody() {
    return page.getPage().body;
  }
  Header& getPageHeader() {
    return page.getPage().header;
  }
};

} // namespace page

#endif  // TOYBOX_PAGE_H
