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

    bool is_move_fwd;
    bool is_move_bwd;

    void create(float aspect_ratio);
    void update(void);
  };
} // namespace Core
