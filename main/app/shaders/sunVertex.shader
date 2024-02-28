#version 330 core

precision highp float;

layout(location = 0) in vec3 vertexPosition;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main() {
	vec4 worldPosition = vec4(vertexPosition, 1) * M;
	vec4 finalPosition = worldPosition * V * P;
	gl_Position = finalPosition;
}