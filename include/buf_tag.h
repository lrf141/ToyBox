//
// Created by lrf141 on 1/22/24.
//

#ifndef TOYBOX_BUF_TAG_H
#define TOYBOX_BUF_TAG_H

#include "tablespace_type.h"
#include "page_type.h"

namespace buf {

struct Tag {
  tablespace_id tablespaceId;
  page_id pageId;

  bool isEqual(Tag &tag) {
    return tablespaceId == tag.tablespaceId && pageId == tag.pageId;
  }
};

}

#endif  // TOYBOX_BUF_TAG_H
