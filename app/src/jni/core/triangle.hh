// SPDX-License-Identifier: MIT

#pragma once

#include <GLES3/gl32.h>

namespace Core {
  struct Triangle {
    GLuint vao;
    GLuint vbo;

    // clang-format off
    GLfloat verts[9] = {
      0.0f,  1.0f, 0.0f,
     -1.0f, -1.0f, 0.0f,
      1.0f, -1.0f, 0.0f
    };
    // clang-format on

    void create(void);
    void destroy(void);
  };
} // namespace Core
