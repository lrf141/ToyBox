#ifndef AVID_PAGE_H
#define AVID_PAGE_H

#include <stdint.h>

// 8 byte
#define PAGE_HEADER_SIZE 8

// 4KB
#define PAGE_SIZE 4096

// PAGE_SIZE - PAGE_HEADER_SIZE
#define PAGE_BODY_SIZE (PAGE_SIZE - PAGE_HEADER_SIZE)

typedef struct Page_Header Page_Header;
typedef struct Page Page;

struct Page_Header {
  uint32_t page_id;
  uint32_t tupleCount;
};

struct Page {
  Page_Header pageHeader;
  uint8_t body[PAGE_BODY_SIZE];
};

#endif  // AVID_PAGE_H
