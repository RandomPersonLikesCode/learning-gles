// SPDX-License-Identifier: MIT

#include "./texture.hh"

#include "stb_image.h"

#include <GLES3/gl32.h>
#include <SDL3/SDL.h>
#include <cstddef>

void Core::Texture::create(const char *path) {
  std::size_t size = 0;
  stbi_uc    *data = static_cast<stbi_uc *>(SDL_LoadFile(path, &size));

  if (!data) {
    return;
  }

  int width    = 0;
  int height   = 0;
  int channels = 0;

  stbi_uc *tex =
      stbi_load_from_memory(data, size, &width, &height, &channels, 4);

  if (!tex) {
    SDL_free(data);
    return;
  }

  glGenTextures(1, &this->id);
  glBindTexture(GL_TEXTURE_2D, this->id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, tex);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(tex);
  SDL_free(data);
}

void Core::Texture::destroy(void) {
  glDeleteTextures(1, &this->id);
}
