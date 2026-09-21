// SPDX-License-Identifier: MIT

#define STB_IMAGE_IMPLEMENTATION

#include "../core/camera.hh"
#include "../core/display.hh"
#include "../core/shader.hh"
#include "../core/shapes.hh"
#include "../core/texture.hh"
#include "stb_image.h"

#include <GLES3/gl32.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glm/gtc/type_ptr.hpp>

int main(int argc, char **argv) {
  stbi_set_flip_vertically_on_load(true);

  Core::Display dp = {};
  dp.config.title  = "GLES Template";
  dp.config.width  = 800;
  dp.config.height = 600;

  if (!dp.create()) {
    return false;
  }

  glViewport(0, 0, dp.config.width_px, dp.config.height_px);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glEnable(GL_DEPTH_TEST);

  Core::Camera cam = {};
  cam.create(dp.config.aspect_ratio);

  Core::Program prog = {};
  prog.create();

  Core::Cube cube = {};
  cube.create();

  Core::Texture metal = {};
  metal.create("textures/metal.png");

  Uint64 last       = SDL_GetTicksNS();
  bool   is_running = true;
  while (is_running) {
    SDL_Event events = {};

    while (SDL_PollEvent(&events)) {
      switch (events.type) {
        case SDL_EVENT_QUIT:
          is_running = false;

          break;
        case SDL_EVENT_FINGER_DOWN:
          if (!(events.tfinger.x < 0.5f && events.tfinger.y > 0.5f)) {
            break;
          }

          if (events.tfinger.y < 0.75f) {
            cam.is_move_fwd = true;
          }

          if (events.tfinger.y > 0.75f) {
            cam.is_move_bwd = true;
          }

          break;
        case SDL_EVENT_FINGER_UP:
          cam.is_move_fwd = false;
          cam.is_move_bwd = false;
      }
    }

    Uint64 current = SDL_GetTicksNS();

    double dt = static_cast<double>((current - last)) / SDL_NS_PER_SECOND;

    last = current;

    float cam_speed = 2.5f * dt;

    if (cam.is_move_fwd) {
      cam.position += cam_speed * cam.front;
    }

    if (cam.is_move_bwd) {
      cam.position -= cam_speed * cam.front;
    }

    cam.update();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(prog.id);
    glBindVertexArray(cube.vao);

    glUniform1i(prog.uniforms.tex, 0);
    glUniformMatrix4fv(prog.uniforms.model, 1, GL_FALSE,
                       glm::value_ptr(cam.model));
    glUniformMatrix4fv(prog.uniforms.view, 1, GL_FALSE,
                       glm::value_ptr(cam.view));
    glUniformMatrix4fv(prog.uniforms.proj, 1, GL_FALSE,
                       glm::value_ptr(cam.proj));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, metal.id);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    SDL_GL_SwapWindow(dp.window);
  }

  metal.destroy();
  cube.destroy();
  prog.destroy();
  dp.destroy();
  return 0;
}
