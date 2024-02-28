#version 330 core

precision highp float;

in vec3 radiance;
out vec4 fragmentColor;

void main() {
	fragmentColor = vec4(1, 1, 1, 1);
}