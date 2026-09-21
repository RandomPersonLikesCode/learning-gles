// SPDX-License-Identifier: MIT

#include "./camera.hh"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>

void Core::Camera::create(float aspect_ratio) {
  this->position = glm::vec3(0.0f, 0.0f, 5.0f);
  this->front    = glm::vec3(0.0f, 0.0f, -1.0f);

  this->model = glm::mat4(1.0f);
  this->view  = glm::lookAt(this->position, this->position + this->front,
                            glm::vec3(0.0f, 1.0f, 0.0f));
  this->proj =
      glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f);
}

void Core::Camera::update(void) {
  if (this->is_move_fwd) {
    this->position += this->speed * this->front;
  }

  if (this->is_move_bwd) {
    this->position -= this->speed * this->front;
  }

  this->view = glm::lookAt(this->position, this->position + this->front,
                           glm::vec3(0.0f, 1.0f, 0.0f));
}
