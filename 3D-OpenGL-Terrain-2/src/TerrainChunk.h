#ifndef TERRAIN_CHUNK_H
#define TERRAIN_CHUNK_H

#include "TerrainMesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <array>

inline constexpr uint8_t MESHES_PER_CHUNK_X = 100;
inline constexpr uint8_t MESHES_PER_CHUNK_Z = 100;

inline constexpr int CHUNK_WIDTH = MESHES_PER_CHUNK_X * TERRAIN_MESH_WIDTH;
inline constexpr int CHUNK_LENGTH = MESHES_PER_CHUNK_Z * TERRAIN_MESH_LENGTH;
inline constexpr int CHUNK_VERTICES = ( MESHES_PER_CHUNK_X + 1 ) * ( MESHES_PER_CHUNK_Z + 1 );

inline static const char* TERRAIN_FILE = "Data/Terrain/terrain.txt";

struct FaceNormal {
	glm::vec3 first;
	glm::vec3 second;
};

struct TerrainChunk {
	unsigned short _x = 0;
	unsigned short _z = 0;

	std::array<float, CHUNK_VERTICES> _heights = { 0 };
	std::array<glm::vec3, CHUNK_VERTICES> _normals;

	void raise(unsigned short x, unsigned short z, float val, float normalized_length);

	FaceNormal calc_face_normal(int index) const;

	glm::vec3 calc_normal(int index);
	void calc_normals();

	bool read(int index);
	bool save(int total_chunks_x) const;
};

#endif