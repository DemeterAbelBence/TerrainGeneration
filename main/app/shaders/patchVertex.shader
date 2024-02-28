#version 330 core

precision highp float;

layout(location = 0) in vec3 vertexPosition;

void main() {
	gl_Position = vec4(vertexPosition, 1);
}