#version 330 core

in vec2 coord;
out vec2 texpos;
uniform sampler2D tex;

void main(void) {
	gl_Position = vec4(coord, 0.0, 1.0);
	texpos = (coord + 1.0) / 2.0;
}