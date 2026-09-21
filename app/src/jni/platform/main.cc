// SPDX-License-Identifier: MIT

#define STB_IMAGE_IMPLEMENTATION

#include "../core/display.hh"
#include "../core/shader.hh"
#include "../core/shapes.hh"
#include "../core/texture.hh"
#include "stb_image.h"

#include <GLES3/gl32.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

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

  glEnable(GL_DEPTH_TEST);

  Core::Program prog = {};
  prog.create();

  Core::Cube cube = {};
  cube.create();

  stbi_set_flip_vertically_on_load(true);

  Core::Texture metal = {};
  metal.create("textures/metal.png");

  GLint tex   = glGetUniformLocation(prog.id, "tex");
  GLint model = glGetUniformLocation(prog.id, "model");
  GLint view  = glGetUniformLocation(prog.id, "view");
  GLint proj  = glGetUniformLocation(prog.id, "proj");

  glm::vec3 cam_pos   = glm::vec3(0.0f, 0.0f, 5.0f);
  glm::vec3 cam_front = glm::vec3(0.0f, 0.0f, -1.0f);

  glm::mat4 model_mat(1.0f);
  glm::mat4 view_mat = glm::lookAt(cam_pos, cam_pos + cam_front,
                                   glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 proj_mat = glm::perspective(
      glm::radians(45.0f), dp.config.aspect_ratio, 0.1f, 100.0f);

  bool  is_running = true;
  float deg        = 0.0f;

  Uint64 last = SDL_GetTicksNS();
  while (is_running) {
    SDL_Event events = {};

    while (SDL_PollEvent(&events)) {
      switch (events.type) {
        case SDL_EVENT_QUIT:
          is_running = false;

          break;
      }
    }

    Uint64 current = SDL_GetTicksNS();

    double dt = static_cast<double>((current - last)) / SDL_NS_PER_SECOND;

    last = current;

    deg += 100.0f * dt;

    model_mat = glm::rotate(glm::mat4(1.0f), glm::radians(deg),
                            glm::vec3(1.0f, 1.0f, 0.0f));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(prog.id);
    glBindVertexArray(cube.vao);

    glUniform1i(tex, 0);
    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(model_mat));
    glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(view_mat));
    glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(proj_mat));

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
