// SPDX-License-Identifier: MIT

#include "./shader.hh"

#include <GLES3/gl32.h>
#include <SDL3/SDL.h>

void Core::Shader::create(const char *path, GLenum type) {
  char *data = static_cast<char *>(SDL_LoadFile(path, nullptr));

  this->id = glCreateShader(type);
  glShaderSource(this->id, 1, &data, nullptr);
  glCompileShader(this->id);

  GLint is_ok = GL_FALSE;
  glGetShaderiv(this->id, GL_COMPILE_STATUS, &is_ok);

  if (is_ok != GL_TRUE) {
    char msg_buff[512] = "";
    glGetShaderInfoLog(this->id, sizeof(msg_buff), nullptr, msg_buff);
  }

  SDL_free(data);
}

void Core::Program::create(void) {
  Core::Shader vert = {};
  vert.create("vertex.glsl", GL_VERTEX_SHADER);

  Core::Shader frag = {};
  frag.create("fragment.glsl", GL_FRAGMENT_SHADER);

  this->id = glCreateProgram();
  glAttachShader(this->id, vert.id);
  glAttachShader(this->id, frag.id);
  glLinkProgram(this->id);

  GLint is_ok = GL_FALSE;
  glGetProgramiv(this->id, GL_LINK_STATUS, &is_ok);

  if (is_ok != GL_TRUE) {
    char msg_buff[512] = "";
    glGetProgramInfoLog(this->id, sizeof(msg_buff), nullptr, msg_buff);
  }
}

Core::Shader::~Shader(void) {
  glDeleteShader(this->id);
}

Core::Program::~Program(void) {
  glDeleteProgram(this->id);
}
