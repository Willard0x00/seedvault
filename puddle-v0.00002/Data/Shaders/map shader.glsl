@Vertex
#version 450 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 uv;
layout (location = 2) in float tile;

uniform mat4 projection;

uniform float lines;

uniform int width;
uniform int height;
uniform int tileWidth;
uniform int tileHeight;

uniform double uvWidth;
uniform double uvHeight;
uniform double uvXOffset;
uniform double uvYOffset;

out vec2 textureCoords;

out float fLines;

void main() {
	float xOffset = gl_InstanceID % width;
	float yOffset = gl_InstanceID / width;
	gl_Position = projection * vec4((vertex.x * tileWidth) + (xOffset * tileWidth), (vertex.y * tileHeight) + (yOffset * tileHeight), 0, 1);

	int t = int(tile);
	double x = (uv.x * uvWidth + (t % 10) * uvWidth) + ((t % 10) * uvXOffset) + uvXOffset;
	double y = (uv.y * uvHeight + (t / 10) * uvHeight) + ((t / 10) * uvYOffset) + uvYOffset;

	textureCoords = vec2(x, y);
	fLines = lines;
}

@End
@Fragment
#version 450 core

layout (location = 0) out vec4 fColor;

uniform sampler2D image;

in vec2 textureCoords;

in float fLines;

void main() {
	if (fLines > 0) {
		fColor = vec4(.8, .8, .8, .8);
	}
	else {
		fColor = texture(image, textureCoords);
		if (fColor.a < .8f) {
     	   	discard;
		}
	}
}

@End
