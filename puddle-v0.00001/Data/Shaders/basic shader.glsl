#Vertex
#version 450 core

layout (location = 0) in vec2 vertex;

uniform mat4 projection;
uniform mat4 model;
uniform int frame;

out vec2 textureCoords;

void main() {
	textureCoords = vec2((vertex.x * .5) + (frame * .5), vertex.y);
	gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}

#End
#Fragment
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

#End
