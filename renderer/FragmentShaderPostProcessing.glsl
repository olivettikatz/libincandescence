#version 330 core

uniform sampler2D tex;
in vec2 texpos;
out vec4 color;

void main(void) {
	color = texture(tex, texpos);
}