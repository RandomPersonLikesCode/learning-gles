// SPDX-License-Identifier: MIT

#pragma once

#include <GLES3/gl3.h>

namespace Core {
  struct Shader {
    GLuint id;

    void create(const char *path, GLenum type);
    void destroy(void);
  };

  struct Program {
    GLuint id;

    void create(void);
    void destroy(void);
  };
} // namespace Core
