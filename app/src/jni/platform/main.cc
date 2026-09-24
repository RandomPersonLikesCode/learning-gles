// SPDX-License-Identifier: MIT

#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION

#include "../core/camera.hh"
#include "../core/display.hh"
#include "../core/shader.hh"
#include "../core/shapes.hh"
#include "../core/texture.hh"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"
#include "stb_image.h"

#include <GLES3/gl32.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cmath>
#include <glm/common.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

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

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGui::StyleColorsDark();

  ImGuiStyle &style   = ImGui::GetStyle();
  float       scaling = dp.config.scaling - 0.5f;
  style.ScaleAllSizes(scaling);
  style.FontScaleDpi = scaling;

  ImGui_ImplSDL3_InitForOpenGL(dp.window, dp.context);
  ImGui_ImplOpenGL3_Init("#version 300 es");

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
    Uint64 current = SDL_GetTicksNS();

    double dt = static_cast<double>((current - last)) / SDL_NS_PER_SECOND;

    last = current;

    SDL_Event events = {};
    while (SDL_PollEvent(&events)) {
      ImGui_ImplSDL3_ProcessEvent(&events);
      ImGuiIO &io = ImGui::GetIO();

      if (io.WantCaptureMouse | io.WantTextInput) {
        continue;
      }

      switch (events.type) {
        case SDL_EVENT_QUIT:
          is_running = false;

          break;
        case SDL_EVENT_FINGER_UP:
          cam.is_first_touch = true;

          break;
        case SDL_EVENT_FINGER_MOTION:
          cam.finger.pos_x = events.tfinger.x * dp.config.width_px;
          cam.finger.pos_y = events.tfinger.y * dp.config.height_px;

          if (cam.is_first_touch) {
            cam.finger.last_pos_x = cam.finger.pos_x;
            cam.finger.last_pos_y = cam.finger.pos_y;

            cam.is_first_touch = false;
          }

          // TODO: Make the finger doesn't interfere with
          // each other

          if (events.tfinger.x > 0.5f) {
            cam.finger.offset_x = cam.finger.pos_x - cam.finger.last_pos_x;
            cam.finger.offset_y = cam.finger.last_pos_y - cam.finger.pos_y;
            cam.finger.last_pos_x = cam.finger.pos_x;
            cam.finger.last_pos_y = cam.finger.pos_y;

            cam.finger.offset_x *= cam.sensitivity;
            cam.finger.offset_y *= cam.sensitivity;

            cam.yaw += cam.finger.offset_x;
            cam.pitch += cam.finger.offset_y;

            cam.pitch = glm::clamp(cam.pitch, -89.0f, 89.0f);

            glm::vec3 dir;

            dir.x = std::cos(glm::radians(cam.yaw))
                  * std::cos(glm::radians(cam.pitch));
            dir.y = std::sin(glm::radians(cam.pitch));
            dir.z = std::sin(glm::radians(cam.yaw))
                  * std::cos(glm::radians(cam.pitch));

            cam.front = glm::normalize(dir);
          }

          if (events.tfinger.x < 0.5f) {
            cam.finger.offset_y = cam.finger.last_pos_y - cam.finger.pos_y;
            cam.finger.last_pos_y = cam.finger.pos_y;

            // TODO: Make the camera movement based on the
            // finger's offset instead of fixed speed

            if (cam.finger.offset_y > 0) {
              cam.position -= cam.speed * cam.front;
            }

            if (cam.finger.offset_y < 0) {
              cam.position += cam.speed * cam.front;
            }
          }

          break;
      }
    }

    cam.speed = 5.0f * dt;

    cam.update();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Test window");

    ImGui::Text("Lorem ipsum");

    ImGui::End();

    ImGui::ShowDemoWindow();

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

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(dp.window);
  }

  metal.destroy();
  cube.destroy();
  prog.destroy();

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();

  dp.destroy();
  return 0;
}
