// SPDX-License-Identifier: MIT

#pragma once

#include <GLES3/gl32.h>

namespace Core {
  struct Texture {
    GLuint id;

    void create(const char *path);
    void destroy(void);
  };
} // namespace Core
