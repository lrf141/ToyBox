//
// Created by lrf141 on 9/23/23.
//

#ifndef TOYBOX_FILE_CONFIG_H
#define TOYBOX_FILE_CONFIG_H

#include <my_sys.h>

namespace file_config {
// Error handling flag. See "my_sys.h".
constexpr const int MYF_STRICT_MODE = (MY_FAE | MY_WME);
constexpr const int MYF_THROUGH_ALL_ERRORS = 0;
}

#endif  // TOYBOX_FILE_CONFIG_H
