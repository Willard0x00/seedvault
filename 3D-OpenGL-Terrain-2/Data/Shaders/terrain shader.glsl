#Vertex

#version 450 core

const int vertex_indices[6] = {2, 0, 1, 2, 3, 1};

layout (location=0) in vec2 vertex;

layout (binding = 0) uniform samplerBuffer heights;
layout (binding = 1) uniform samplerBuffer normals;

uniform int mesh_width;
uniform int mesh_length;

uniform int meshes_per_chunk_x;
uniform int meshes_per_chunk_z;
uniform int chunk_x;
uniform int chunk_z;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VS {
	float height;
	vec3  position;
	vec3  normal;
} dest;

float get_height(int vertex) {
	int index = gl_InstanceID + (gl_InstanceID / meshes_per_chunk_x);

	switch(vertex_indices[vertex]) {
		case 0: return texelFetch(heights, index).r;								
		case 1: return texelFetch(heights, index + 1).r;							
		case 2: return texelFetch(heights, index + (meshes_per_chunk_x + 1)).r;		
		case 3: return texelFetch(heights, index + 1 + (meshes_per_chunk_x + 1)).r; 
	}

	return 0;
}

vec3 get_normal(int vertex) {
	int index = gl_InstanceID + (gl_InstanceID / meshes_per_chunk_x);

	switch(vertex_indices[vertex]) {
		case 0: return texelFetch(normals, index).xyz;
		case 1:	return texelFetch(normals, index + 1).xyz;
		case 2:	return texelFetch(normals, index + (meshes_per_chunk_x + 1)).xyz;
		case 3:	return texelFetch(normals, index + 1 + (meshes_per_chunk_x + 1)).xyz;
	}
}

vec3 calc_instance_position() {
	return vec3(gl_InstanceID % meshes_per_chunk_x, 0, gl_InstanceID / meshes_per_chunk_z);
}

vec3 get_position() {
	vec3 instance_position = calc_instance_position();
	vec3 position;
	position.x = mesh_width * (vertex.x + instance_position.x + (chunk_x * meshes_per_chunk_x));
	position.z = mesh_length * (vertex.y + instance_position.z + (chunk_z * meshes_per_chunk_z));
	position.y = get_height(gl_VertexID);

	return position;
}

void main() {
	vec3 position = get_position();

	gl_Position = projection * view * vec4(position, 1.0);
	
	dest.height = position.y;
	dest.position = position;
	dest.normal = get_normal(gl_VertexID);
}

#End

#Fragment

#version 450 core

layout (location=0) out vec3 f_color;

in VS {
	float height;
	vec3  position;
	vec3  normal;
} source;

void main() {

	vec3 normal = normalize(source.normal);
	vec3 light_pos = vec3(0, 50, 0);
	vec3 light_dir = normalize(light_pos - source.position);

	float diff = clamp(dot(normal, light_dir), 0, 1);
	vec3 diffuse = diff * vec3(.4, 0, 0);
	vec3 ambient = vec3(.5, .5, .5);

	vec3 color = vec3(.4, .1, .1);
	f_color = (ambient + diffuse) * color;
	//f_color = vec4(source.height / 100.0f, .25, .25, 1);
}

#End