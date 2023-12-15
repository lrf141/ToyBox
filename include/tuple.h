//
// Created by lrf141 on 9/30/23.
//
#ifndef TUPLE_TUPLE_H
#define TUPLE_TUPLE_H

#include <cinttypes>
#include <vector>

namespace tuple {

class Tuple {
 private:
  uint8_t nullBitmask;
  std::vector<uint8_t> data;
 public:
  Tuple(uint32_t size, uint8_t nullBitmask)
      : nullBitmask(nullBitmask), data(size) {}
  Tuple(uint32_t size, uint8_t nullBitmask, uint8_t *data)
      : nullBitmask(nullBitmask), data(size){
    memcpy(this->data.data(), data, size);
  }
  ~Tuple() {
  }
  uint32_t getSize() {
    return this->data.size();
  }

  uint8_t *getData() {
    return this->data.data();
  }
};

} // namespace tuple

#endif  // TUPLE_TUPLE_H
