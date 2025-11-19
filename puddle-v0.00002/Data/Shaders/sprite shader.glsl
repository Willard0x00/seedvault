@Vertex
#version 450 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 uv;

uniform mat4 projection;
uniform mat4 model;

uniform int frame;

uniform int width;
uniform int height;

uniform double uvWidth;
uniform double uvHeight;
uniform double uvXOffset;
uniform double uvYOffset;

out vec2 textureCoords;

void main() {
	gl_Position = projection * model * vec4(vertex.x * width, vertex.y * height, 0, 1);

	double x = (uv.x * uvWidth + (frame % 10) * uvWidth) + ((frame % 10) * uvXOffset) + uvXOffset;
	double y = (uv.y * uvHeight + (frame / 10) * uvHeight) + ((frame / 10) * uvYOffset) + uvYOffset;

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
	if (fColor.a < .8f) {
     	   discard;
	}
}

@End
