//
// Created by lrf141 on 9/25/23.
//
#include "page.h"
#include "file_util.h"
#include "file_config.h"

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

void PageHandler::read(file_handler::FileDescriptor fd) {
  FileUtil::seek(fd, PAGE_START_POSITION + page.getPageId() * PAGE_SIZE,
                 SEEK_SET, MYF(file_config::MYF_STRICT_MODE));
  size_t readSize = FileUtil::read(fd, page.toBinary(), PAGE_SIZE);
  assert(readSize == PAGE_SIZE);
}

} // namespace page
