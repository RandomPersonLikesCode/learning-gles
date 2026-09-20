// SPDX-License-Identifier: MIT

#include "./triangle.hh"

#include <GLES3/gl32.h>

void Core::Triangle::create(void) {
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(this->vao);

  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(this->verts), this->verts,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        static_cast<void *>(0));
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

void Core::Triangle::destroy(void) {
  glDeleteVertexArrays(1, &this->vao);
  glDeleteBuffers(1, &this->vbo);
}
