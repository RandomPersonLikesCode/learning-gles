#version 320 es

precision mediump float;

uniform sampler2D tex;

in vec2 uv;

out vec4 final_col;

void main(void) {
  final_col = texture(tex, uv);
}
