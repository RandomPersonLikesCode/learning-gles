// SPDX-License-Identifier: MIT

#include "../core/display.hh"
#include "../core/shader.hh"

#include <GLES3/gl32.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

GLfloat verts[] = {
  0.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f,
};

int main(int argc, char **argv) {
  Core::Display dp = {};
  dp.config.title  = "GLES Template";
  dp.config.width  = 800;
  dp.config.height = 600;

  if (!dp.create()) {
    return false;
  }

  glViewport(0, 0, dp.config.width_px, dp.config.height_px);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  Core::Program prog = {};
  prog.create();

  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        static_cast<void *>(0));

  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  bool is_running = true;
  while (is_running) {
    SDL_Event events = {};

    while (SDL_PollEvent(&events)) {
      switch (events.type) {
        case SDL_EVENT_QUIT:
          is_running = false;

          break;
      }
    }
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(prog.id);
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(dp.window);
  }

  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  return 0;
}
