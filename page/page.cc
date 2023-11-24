//
// Created by lrf141 on 9/25/23.
//
#include "page.h"
#include <iostream>
#include "file_config.h"
#include "file_util.h"

namespace page {

PageHandler PageHandler::reserveNewPage(page_id newPageId) {
  return PageHandler(newPageId);
}

void PageHandler::flush(file_handler::FileDescriptor fd) {
  FileUtil::seek(fd, PAGE_START_POSITION + page.getPageId() * PAGE_SIZE,
                 SEEK_SET, MYF(file_config::MYF_STRICT_MODE));
  size_t writeSize = FileUtil::write(fd, page.toBinary(), PAGE_SIZE);
  assert(writeSize == PAGE_SIZE);
}

void PageHandler::readFromFile(file_handler::FileDescriptor fd) {
  FileUtil::seek(fd, PAGE_START_POSITION + page.getPageId() * PAGE_SIZE,
                 SEEK_SET, MYF(file_config::MYF_STRICT_MODE));
  size_t readSize = FileUtil::read(fd, page.toBinary(), PAGE_SIZE);
  assert(readSize == PAGE_SIZE);
}

void PageHandler::insert(tuple::Tuple t) {
  page::Header &header = page.getHeader();
  uint32_t tupleSize = t.getSize();
  uint8_t *tupleData = t.getData();
  page::Slot newSlot = Slot{
      header.freeEnd - tupleSize,
      tupleSize
  };
  // TODO: page split
  memcpy((page.getPage().body + header.freeBegin),
         reinterpret_cast<uchar *>(&newSlot), page::SLOT_SIZE);
  memcpy((page.getPage().body + header.freeEnd - tupleSize),
         tupleData, tupleSize);
  header.freeBegin += page::SLOT_SIZE;
  header.freeEnd -= tupleSize;
}

tuple::Tuple PageHandler::readTuple(uint64_t tupleId) {
  page::Slot targetSlot = *reinterpret_cast<Slot *>
                          (page.getPage().body + SLOT_SIZE * tupleId);
  uchar *tupleBody = static_cast<uchar *>(page.getPage().body + targetSlot.recordStartOffset);
  return tuple::Tuple(targetSlot.size, 0, tupleBody);
}

} // namespace page
