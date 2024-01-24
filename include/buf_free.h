//
// Created by lrf141 on 1/24/24.
//

#ifndef TOYBOX_BUF_FREE_H
#define TOYBOX_BUF_FREE_H

#include "buf_frame.h"

namespace buf {

struct FreeElement {
  Frame *freeFrame;
};

} // namespace buf

#endif  // TOYBOX_BUF_FREE_H
