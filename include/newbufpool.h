//
// Created by lrf141 on 1/22/24.
//

#ifndef TOYBOX_NEWBUFPOOL_H
#define TOYBOX_NEWBUFPOOL_H

#include <cinttypes>
#include <queue>
#include <utility>

#include "buf_frame.h"
#include "buf_free.h"
#include "buf_type.h"
#include "buf_util.h"

namespace newBuf {

struct ReferenceDescriptor {
  tablespace_id tablespaceId;
  page_id pageId;
  const char *tablespacePath;
};

struct ReadDescriptor : ReferenceDescriptor {
  uint64_t tupleCursor;
};

struct WriteDescriptor : ReferenceDescriptor {
  tuple::Tuple *tuple;
};

class BufferPool {
 private:
  frame_count_t frameCount;
  buf::Frame *frames;
  std::queue<buf::FreeElement> freeList;

 public:
  BufferPool(frame_count_t frmCount, buf::Frame *frms, std::queue<buf::FreeElement> frlist)
      : frameCount(frmCount),
        frames(frms),
        freeList(std::move(frlist)){}
  ~BufferPool() {
      buf::deinit_buffer_pool(this->frames);
  }
  buf::Frame *getFrame(buf::Tag tag);
  bool existPage(buf::Tag tag);
  int evictFrame(buf::Tag tag);
  bool hasFreeFrame();
  buf::Frame *getFirstEmptyFrame();
  page::PageHandler *readFromTablespace(ReferenceDescriptor referenceDescriptor);
  int read(uchar *buf, ReadDescriptor readDescriptor);
  void write(WriteDescriptor writeDescriptor);
};
}

#endif  // TOYBOX_NEWBUFPOOL_H
