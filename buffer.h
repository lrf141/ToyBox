#ifndef MYSQL_BUFFER_H
#define MYSQL_BUFFER_H

#include <stdlib.h>

#include "page.h"

typedef struct BufferPool BufferPool;

struct BufferPool {
  Page *pages;
};

#endif  // MYSQL_BUFFER_H
