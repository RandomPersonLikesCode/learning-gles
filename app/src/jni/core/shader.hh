// SPDX-License-Identifier: MIT

#pragma once

#include <GLES3/gl3.h>

namespace Core {
  struct Shader {
    GLuint id;

    void create(const char *path, GLenum type);
    ~Shader(void);
  };

  struct Program {
    GLuint id;

    void create(void);
    ~Program(void);
  };
} // namespace Core
