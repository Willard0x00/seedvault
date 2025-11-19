#Vertex
#version 450 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in float tile;

uniform mat4 projection;
uniform mat4 model;
uniform vec2 tileSize;
uniform int width;
uniform int height;
uniform int tileSheetWidth;
uniform int tileSheetHeight;

out vec2 textureCoords;

void main() {
	float xOffset = (gl_InstanceID % width) * tileSize.x;
	float yOffset = (gl_InstanceID / width) * tileSize.y;

	gl_Position = projection * model *
	vec4( vertex.x * tileSize.x + xOffset,
		  vertex.y * tileSize.y + yOffset,
		  0.0,
		  1.0
	);

	float xTileScalar = tileSize.x / float(tileSheetWidth);
	float yTileScalar = tileSize.y / float(tileSheetHeight);
	textureCoords = vec2((vertex.x * xTileScalar) + ((int(tile) % 50) * xTileScalar),
						 (vertex.y * yTileScalar) + ((int(tile) / 50) * yTileScalar)
				    );
}

#End
#Fragment
#version 450 core

layout (location = 0) out vec4 f_color;

uniform sampler2D image;

in vec2 textureCoords;

void main() {
	f_color = texture(image, textureCoords); 
	
	//f_color = vec4(outT, 0, 0, 0);
}

#End
