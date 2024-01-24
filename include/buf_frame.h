//
// Created by lrf141 on 1/22/24.
//

#ifndef TOYBOX_BUF_FRAME_H
#define TOYBOX_BUF_FRAME_H

#include "buf_tag.h"
#include "buf_type.h"
#include "page.h"

namespace buf {

struct Frame {
  Tag tag;
  frame_ref_count_t ref;
  bool isDirty;
  page::PageHandler *pageHandler;
  Frame *next;
  int writeBackPage();
};

typedef struct Frame Frame;

}

#endif  // TOYBOX_BUF_FRAME_H
