// SPDX-License-Identifier: MIT

#pragma once

#include <SDL3/SDL.h>

namespace Core {
  struct Display {
    SDL_Window   *window;
    SDL_GLContext context;

    struct {
      const char *title;

      int   width;
      int   height;
      int   width_px;
      int   height_px;
      float aspect_ratio;
      float scaling;
    } config;

    bool create(void);
    void destroy(void);
  };
} // namespace Core
