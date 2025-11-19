@Vertex
#version 450 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 position;
layout (location = 3) in float frame;

uniform mat4 projection;
uniform mat4 model;

uniform int width;
uniform int height;

uniform double uvWidth;
uniform double uvHeight;
uniform double uvXOffset;
uniform double uvYOffset;

out vec2 textureCoords;

void main() {
	gl_Position = projection * vec4(vertex.x * width + position.x, vertex.y * height + position.y, 0, 1);

	int iFrame = int(frame);
	double x = (uv.x * uvWidth + (iFrame % 10) * uvWidth) + ((iFrame % 10) * uvXOffset) + uvXOffset;
	double y = (uv.y * uvHeight + (iFrame / 10) * uvHeight) + ((iFrame / 10) * uvYOffset) + uvYOffset;

	textureCoords = vec2(x, y);
}

@End
@Fragment
#version 450 core

layout (location = 0) out vec4 fColor;

uniform sampler2D image;

in vec2 textureCoords;

void main() {
	fColor = texture(image, textureCoords);
	if (fColor.a < 0.8f) {
     	   discard;
	}
}

@End
