#ifndef AVID_PAGE_H
#define AVID_PAGE_H

#include <stdint.h>

// 1 byte
#define PAGE_HEADER_SIZE 1

// 4KB
#define PAGE_SIZE 4096

typedef struct Page_Header Page_Header;
typedef struct Page Page;

struct Page_Header {
  uint8_t page_id;
};

struct Page {
  Page_Header pageHeader;
  uint8_t body[PAGE_SIZE - sizeof(uint8_t) * PAGE_HEADER_SIZE];
};

#endif  // AVID_PAGE_H
