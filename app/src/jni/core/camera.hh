// SPDX-License-Identifier: MIT

#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

namespace Core {
  struct Camera {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;

    glm::vec3 position;
    glm::vec3 front;

    float speed;
    float sensitivity = 0.2f;
    float yaw         = -90.0f;
    float pitch;

    struct {
      float pos_x;
      float pos_y;
      float last_pos_x;
      float last_pos_y;
      float offset_x;
      float offset_y;
    } finger;

    bool is_first_touch = true;

    void create(float aspect_ratio);
    void update(void);
  };
} // namespace Core
