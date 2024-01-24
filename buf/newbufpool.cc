//
// Created by lrf141 on 1/22/24.
//

#include "newbufpool.h"

namespace newBuf {

buf::Frame *BufferPool::getFrame(buf::Tag tag) {
  for (buf::Frame *frame = this->frames; frame->next != nullptr; frame = frame->next) {
    if (frame->tag.isEqual(tag)) {
      frame->ref++;
      return frame;
    }
    frame = frame->next;
  }
  return nullptr;
}

bool BufferPool::existPage(buf::Tag tag){
  for (buf::Frame *frame = this->frames; frame->next != nullptr; frame = frame->next) {
    if (frame->pageHandler == nullptr) {
      continue;
    }
    if (frame->tag.isEqual(tag)) {
      return true;
    }
    frame = frame->next;
  }
  return false;
}

int BufferPool::evictFrame(buf::Tag tag) {
  buf::Frame *frame = getFrame(tag);
  if (frame == nullptr) {
    // このパターンは現状存在しないはず
  }
}

bool BufferPool::hasFreeFrame() {
  return !this->freeList.empty();
}

buf::Frame *BufferPool::getFirstEmptyFrame() {
  buf::Frame *freeFrame = this->freeList.front().freeFrame;
  this->freeList.pop();
  return freeFrame;
}

page::PageHandler *BufferPool::readFromTablespace(ReferenceDescriptor referenceDescriptor) {

}

int BufferPool::read(uchar *buf, newBuf::ReadDescriptor readDescriptor) {
  buf::Tag tag{readDescriptor.tablespaceId, readDescriptor.pageId};
  buf::Frame *targetFrame = nullptr;
  if (!hasFreeFrame()) {
    evictFrame({readDescriptor.tablespaceId, readDescriptor.pageId});
    page::PageHandler *pageHandler = readFromTablespace(ReferenceDescriptor(readDescriptor));
    buf::Frame *frame = getFirstEmptyFrame();
    frame->pageHandler = pageHandler;
    targetFrame = frame;
  }

  if (targetFrame == nullptr) {
    targetFrame = getFrame(tag);
  }
  // TODO: targetFrame はここで nullptr になる可能性があるがイケてないのでどうにかする
  // TODO: ここのポインタもイケてない → 冷静になると free な状態で pageHandler に何入れたらいいか怪しいのでポインタでいい気がしてきた
  page::PageHandler* pageHandler = targetFrame->pageHandler;
  tuple::Tuple tuple = pageHandler->readTuple(readDescriptor.tupleCursor);
  memcpy(buf, tuple.getData(), tuple.getSize());
  return tuple.getSize();
}

void BufferPool::write(newBuf::WriteDescriptor writeDescriptor) {

}

} // namespace newBuf
