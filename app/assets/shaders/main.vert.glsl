#version 320 es

precision highp float;

layout(location = 0) in vec3 org_pos;
layout(location = 1) in vec2 org_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 uv;

void main(void) {
  gl_Position = proj * view * model * vec4(org_pos, 1.0);

  uv = org_uv;
}
