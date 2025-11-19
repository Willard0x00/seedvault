@Vertex
#version 450 core

layout (location = 0) in vec2 vertex;

uniform mat4 projection;

uniform vec4 rect;
uniform vec4 color;

uniform bool center;

out vec4 fragColor;

void main() {
	vec2 position = vec2(vertex.x, vertex.y);
	if (!center) {
		position.x += 0.5f;
		position.y += 0.5f;
	}
	gl_Position = projection * vec4(position.x + rect.x + (position.x * rect.z), position.y + rect.y + (position.y * rect.w), 0, 1);
	fragColor = color;
}

@End
@Fragment
#version 450 core

layout (location = 0) out vec4 fColor;

in vec4 fragColor;

void main() {
	fColor = fragColor;
}

@End
