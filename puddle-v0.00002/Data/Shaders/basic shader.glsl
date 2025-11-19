@Vertex
#version 450 core

layout (location = 0) in vec2 vertex;

uniform mat4 projection;

void main() {
	gl_Position = projection * vec4(vertex.x, vertex.y, 0, 1);
}

@End
@Fragment
#version 450 core

layout (location = 0) out vec4 fColor;

void main() {
	fColor = vec4(1, 0, 1, 1);
}

@End
