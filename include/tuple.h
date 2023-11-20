//
// Created by lrf141 on 9/30/23.
//
#ifndef TUPLE_TUPLE_H
#define TUPLE_TUPLE_H

#include <cinttypes>

namespace tuple {

class Tuple {
 private:
  uint32_t size;
  uint8_t nullBitmask;
  uint8_t *data;
 public:
  Tuple(uint32_t size, uint8_t nullBitmask)
      : size(size), nullBitmask(nullBitmask), data(new uint8_t[size]()) {}
  Tuple(uint32_t size, uint8_t nullBitmask, uint8_t *data)
      : size(size), nullBitmask(nullBitmask), data((uint8_t *)calloc(size, size * sizeof(uint8_t))){
    memcpy(this->data, data, size);
  }
  ~Tuple() {
    //free(data);
  }
  uint32_t getSize() {
    return size;
  }

  uint8_t *getData() {
    return data;
  }
};

} // namespace tuple

#endif  // TUPLE_TUPLE_H
