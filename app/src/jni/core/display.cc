// SPDX-License-Identifier: MIT

#include "./display.hh"

#include <SDL3/SDL.h>

bool Core::Display::create(void) {
  SDL_SetHint(SDL_HINT_ANDROID_TRAP_BACK_BUTTON, "1");
  SDL_SetHint(SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight");

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                      SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    return false;
  }

  this->window = SDL_CreateWindow(
      this->config.title, this->config.width, this->config.height,
      SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);

  if (!this->window) {
    return false;
  }

  this->context = SDL_GL_CreateContext(this->window);

  if (!this->context) {
    return false;
  }

  SDL_GL_MakeCurrent(this->window, this->context);
  SDL_GL_SetSwapInterval(1);

  SDL_GetWindowSize(this->window, &this->config.width,
                    &this->config.height);

  SDL_GetWindowSizeInPixels(this->window, &this->config.width_px,
                            &this->config.height_px);

  this->config.aspect_ratio =
      static_cast<float>(this->config.width) / this->config.height;
  this->config.scaling =
      SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

  return true;
}

Core::Display::~Display(void) {
  SDL_GL_MakeCurrent(nullptr, nullptr);

  SDL_GL_DestroyContext(this->context);
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}
