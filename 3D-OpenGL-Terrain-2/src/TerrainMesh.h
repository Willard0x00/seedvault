#ifndef TERRAIN_MESH_H
#define TERRAIN_MESH_H

#include <GL/gl3w.h>
#include <cstdint>

struct Program;
struct TerrainChunk;

inline constexpr uint8_t TERRAIN_MESH_WIDTH = 1;
inline constexpr uint8_t TERRAIN_MESH_LENGTH = 1;

struct TileVertex {
	GLfloat position[2];
};

class TerrainMesh {
public:
	TerrainMesh(Program* program);
	~TerrainMesh();

	void draw(TerrainChunk* chunk);
private:
	void init();
private:
	GLuint			_vao;
	GLuint			_vertex_buffer;
	GLuint			_height_buffer;
	GLuint			_normal_buffer;

	GLuint			_height_texture;
	GLuint			_normal_texture;

	Program*		_program;
};

#endif