#ifndef TERRAIN_H
#define TERRAIN_H

#include "TerrainMesh.h"
#include "TerrainChunk.h"
#include "TerrainLoader.h"

#include <vector>
#include <array>
#include <thread>

struct Program;

typedef std::vector<TerrainChunk*> TerrainChunks;

class Terrain {
public:
	Terrain(uint8_t depth, Program* mesh_program);
	~Terrain();

	void start_chunk_loader(float* x, float* z);
	void stop_chunk_loader();

	void draw();

	int get_width() const;
	int get_length() const;

	size_t size() const;

	std::vector<TerrainChunk*>* get_chunks();

	void print_array();
private:
	int _width;
	int _length;

	TerrainMesh _mesh;
	TerrainChunks _chunks;
	TerrainLoader _loader;
	
	std::thread _loader_thread;
	bool _loader_started;
};

#endif