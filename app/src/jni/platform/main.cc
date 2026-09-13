// SPDX-License-Identifier: MIT

#include "../core/display.hh"

#include <GLES3/gl32.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

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

    SDL_GL_SwapWindow(dp.window);
  }

  return 0;
}
