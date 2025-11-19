#include "TerrainMesh.h"

#include "Program.h"
#include "Terrain.h"

// ---------TILE MESH----------------
constexpr TileVertex TILE_VERTICES[] = {
	{0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f},
	{0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}
};

// ---------TERRAIN MESH-------------------
TerrainMesh::TerrainMesh(Program* program) :
	_program			( program )
{
	init();
}

TerrainMesh::~TerrainMesh() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vertex_buffer);
	glDeleteBuffers(1, &_height_buffer);
}

void TerrainMesh::init() { 
	glCreateVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glCreateBuffers(1, &_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
	glNamedBufferStorage(_vertex_buffer, sizeof(TILE_VERTICES), TILE_VERTICES, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(TileVertex), reinterpret_cast<void*>(offsetof(TileVertex, position)));

	glCreateBuffers(1, &_height_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _height_buffer);
	glNamedBufferStorage(_height_buffer, sizeof(GLfloat) * CHUNK_VERTICES, nullptr, GL_DYNAMIC_STORAGE_BIT);

	glCreateTextures(GL_TEXTURE_BUFFER, 1, &_height_texture);
	glTextureBuffer(_height_texture, GL_R32F, _height_buffer);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_BUFFER, _height_texture);

	glCreateBuffers(1, &_normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _normal_buffer);
	glNamedBufferStorage(_normal_buffer, sizeof(glm::vec3) * CHUNK_VERTICES, nullptr, GL_DYNAMIC_STORAGE_BIT);

	glCreateTextures(GL_TEXTURE_BUFFER, 1, &_normal_texture);
	glTextureBuffer(_normal_texture, GL_RGB32F, _normal_buffer);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_BUFFER, _normal_texture);
}

void TerrainMesh::draw(TerrainChunk* chunk) {
	glBindVertexArray(_vao);
	glUseProgram(_program->_id);

	glActiveTexture(GL_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, _height_buffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * CHUNK_VERTICES, &chunk->_heights[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindBuffer(GL_ARRAY_BUFFER, _normal_buffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * CHUNK_VERTICES, &chunk->_normals[0]);
	
	glUniform1i(glGetUniformLocation(_program->_id, "mesh_width"), TERRAIN_MESH_WIDTH);
	glUniform1i(glGetUniformLocation(_program->_id, "mesh_length"), TERRAIN_MESH_LENGTH);
	glUniform1i(glGetUniformLocation(_program->_id, "meshes_per_chunk_x"), MESHES_PER_CHUNK_X);
	glUniform1i(glGetUniformLocation(_program->_id, "meshes_per_chunk_z"), MESHES_PER_CHUNK_Z);
	glUniform1i(glGetUniformLocation(_program->_id, "chunk_x"), chunk->_x);
	glUniform1i(glGetUniformLocation(_program->_id, "chunk_z"), chunk->_z);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, sizeof(TILE_VERTICES) / sizeof(TileVertex), MESHES_PER_CHUNK_X * MESHES_PER_CHUNK_Z);

}