@Vertex
#version 450 core

const float PI = 3.1415926538f;

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 position;
layout (location = 3) in vec2 scale;
layout (location = 4) in float rotation;
layout (location = 5) in float frame;
layout (location = 6) in float depth;
layout (location = 7) in float highlight;

uniform mat4 projection;
uniform mat4 model;

uniform int width;
uniform int height;

uniform double uvWidth;
uniform double uvHeight;
uniform double uvXOffset;
uniform double uvYOffset;

out vec2 textureCoords;

out float fHighlight;
out float fDepth;

mat2 rotate(float angle) {
	angle *= PI / 180;
	const float s = sin(angle);
	const float c = cos(angle);
	return mat2(c, -s, s, c);
}

void main() {
	vec2 vPosition = vec2(vertex.x * width, vertex.y * height) * scale;

	if (rotation != 0.0f) {
		 vPosition *= rotate(rotation);
	}
	
	gl_Position = projection * vec4(vPosition.x + position.x, vPosition.y + position.y, position.z, 1);

	int iFrame = int(frame);
	double x = (uv.x * uvWidth + (iFrame % 10) * uvWidth) + ((iFrame % 10) * uvXOffset) + uvXOffset;
	double y = (uv.y * uvHeight + (iFrame / 10) * uvHeight) + ((iFrame / 10) * uvYOffset) + uvYOffset;

	textureCoords = vec2(x, y);
	fHighlight = highlight;
	fDepth = depth;
}

@End
@Fragment
#version 450 core

layout (location = 0) out vec4 fColor;
layout (depth_less) out float gl_FragDepth;

uniform sampler2D image;

uniform bool highlight;

in vec2 textureCoords;

in float fHighlight;
in float fDepth;

void main() {
	fColor = texture(image, textureCoords);

	if (fColor.a < 0.8f) {
		discard;
	}
	
	if (fHighlight > 0.0f) {
		fColor.r += 0.2f;
		fColor.a -= 0.2f;
	}

	gl_FragDepth = 1.0f - (fDepth / 100000.0f);

}

@End
