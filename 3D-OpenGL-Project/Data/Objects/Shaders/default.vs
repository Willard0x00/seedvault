#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;

uniform mat4 MVP;
uniform mat4 M;

out vec3 vsPosition;
out vec2 UV;

void main() {
	vsPosition = (M * vec4(vertexPosition, 1.0f)).xyz;

	gl_Position = MVP * vec4(vertexPosition, 1.0f);

	UV = vertexUV;
}