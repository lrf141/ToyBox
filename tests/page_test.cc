//
// Created by lrf141 on 9/26/23.
//
#include <gtest/gtest.h>
#include "page.h"

class PageTest : public testing::Test {
 protected:
  page::PageHandler *sut;

  void SetUp() override {
    sut = new page::PageHandler(1);
  }

  void TearDown() override {
    delete sut;
    sut = nullptr;
  }
};

