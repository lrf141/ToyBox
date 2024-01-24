//
// Created by lrf141 on 1/22/24.
//

#ifndef TOYBOX_BUF_UTIL_H
#define TOYBOX_BUF_UTIL_H

#include <cinttypes>
#include <queue>

#include "newbufpool.h"
#include "buf_frame.h"
#include "buf_type.h"

namespace buf {

frame_count_t calc_max_frame_count(uint64_t maxBufferPoolSize, frame_size_t frameSize) {
  return maxBufferPoolSize / frameSize;
}

buf::Frame *init_buffer_pool_frames(frame_count_t frameCount) {
  buf::Frame *firstFrame = new buf::Frame;

  buf::Frame *tmp = firstFrame;
  for (frame_count_t fc = 1; fc < frameCount; fc++) {
    buf::Frame *newFrame = new buf::Frame;
    tmp->next = newFrame;
    tmp = newFrame;
  }

  return firstFrame;
}

std::queue<FreeElement> init_buffer_pool_free_list(buf::Frame *frames) {
  std::queue<FreeElement> freeList;
  for (buf::Frame *frame = frames; frame->next != nullptr; frame = frame->next) {
    freeList.push({frame});
  }
  return freeList;
}

newBuf::BufferPool *init_buffer_pool(buf_size_t maxBufferPoolSize) {
  frame_size_t frameSize = sizeof(buf::Frame) + page::PAGE_SIZE;
  frame_count_t allocateFrameCount = calc_max_frame_count(maxBufferPoolSize, frameSize);
  buf::Frame *frames = init_buffer_pool_frames(allocateFrameCount);

  newBuf::BufferPool *bufferPool = new newBuf::BufferPool(allocateFrameCount);
  return bufferPool;
}

void write_back_all_frames(buf::Frame *frames) {
  buf::Frame *targetFrame = frames;
  while(targetFrame->next != nullptr) {
    targetFrame->writeBackPage();
    targetFrame = targetFrame->next;
  }
}

void release_all_frames(buf::Frame *frames) {
  for(Frame *frame = frames; frame != nullptr;) {
    Frame *tmp = frame->next;
    delete frame;
    frame = tmp;
  }
}

void deinit_buffer_pool(buf::Frame *frames) {
  if (frames != nullptr) {
    write_back_all_frames(frames);
    release_all_frames(frames);
  }
}

}

#endif  // TOYBOX_BUF_UTIL_H
