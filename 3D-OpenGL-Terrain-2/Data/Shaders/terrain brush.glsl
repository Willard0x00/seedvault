#Vertex

#version 450 core

uniform mat4 projection;
uniform mat4 view;

uniform vec3 position;

out VS {
	vec3 vertex;
} dest;

void main() {
	dest.vertex = vec3(position.x, position.y, position.z);
	gl_Position = projection * view * vec4(position.x, position.y, position.z, 1.0);
}

#End

#Geometry

#version 450 core

layout (points) in;
layout (line_strip, max_vertices = 64) out;

uniform mat4 projection;
uniform mat4 view;

uniform float radius;

const float PI = 3.1415926;

in VS {
    vec3 vertex;
} source[];

void main() {

	for (int i = 0; i <= 64; i++) {
       // Angle between each side in radians
       float ang = PI * 2.0 / 63.0 * i;

        // Offset from center of point (0.3 to accomodate for aspect ratio)

        float x = cos(ang) * radius + source[0].vertex.x;
        float y = source[0].vertex.y;
        float z = -sin(ang) * radius + source[0].vertex.z;

        float h = 0.0f;

        y = h + 0.01f;

        float fx = cos(ang) * radius + source[0].vertex.x;
        float fz = -sin(ang) * radius + source[0].vertex.z;
        vec4 offset = vec4(x, y, z, 1.0);
        gl_Position = projection * view * offset;
        EmitVertex();
    }

    EndPrimitive();
}

#End

#Fragment

#version 450 core

layout (location = 0) out vec3 f_color;

void main() {
	f_color = vec3(1, 0, 0);
}

#End