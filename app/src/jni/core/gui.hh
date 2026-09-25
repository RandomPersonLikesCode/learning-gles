// SPDX-License-Identifier: MIT

#pragma once

#include "imgui.h"

#include <SDL3/SDL.h>

namespace Core {
  namespace Gui {
    void create(SDL_Window *window, SDL_GLContext context, float scaling);
    void destroy(void);

    void update(void);
    void render(void);
  } // namespace Gui
} // namespace Core
