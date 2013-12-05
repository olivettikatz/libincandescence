#version 330 core

in vec2 texpos;
uniform sampler2D tex;
uniform vec4 textColor;
out vec4 color;

void main(void) {
  color = vec4(1, 1, 1, texture(tex, texpos).r) * textColor;
}