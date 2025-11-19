@Vertex
#version 450 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 uv;

uniform mat4 projection;

uniform float x;
uniform float y;

out vec2 textureCoords;

void main() {
	gl_Position = projection * vec4(vertex.x + x, vertex.y, y, 1.0);
	
	float y = vertex.y;
	if (y == 2.0f) {
		y = 1.0f;
	}

	textureCoords = vec2(vertex.x, 1.0 - y);
}

@End
@Fragment
#version 450 core

layout (location = 0) out vec4 f_color;

uniform sampler2D image;

in vec2 textureCoords;

void main() {
	f_color = texture(image, textureCoords); 
    	if (f_color.r <= .1 && f_color.g <= .1 && f_color.b >= .9) {
     	   discard;
   	}
}

@End
