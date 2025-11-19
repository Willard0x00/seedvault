#ifndef TERRAIN_LOADER_H
#define TERRAIN_LOADER_H

#include <fstream>
#include <vector>
#include <cstdint>

class Terrain;
struct TerrainChunk;

class TerrainLoader {
public:
	TerrainLoader(Terrain* terrain, uint8_t loaded_chunk_distance);

	void process_chunk_loading(bool* started, float* x, float* z);

	void debug_write_base_terrain();

	void load_terrain_column(uint8_t direction);
	void load_terrain_row(uint8_t direction);

	int new_chunk_index(TerrainChunk* chunk, int x_offset, int z_offset) const;
private:
	bool is_first_index_in_row(int index, int width) const;
	bool is_last_index_in_row(int index, int width) const;
	bool is_first_index_in_column(int index, int width) const;
	bool is_last_index_in_column(int index, int width, int size) const;

	int min_x() const;
	int max_x() const;
	int min_z() const;
	int max_z() const;

	int iterate_on_column(int i, int width, int size) const;
	int riterate_on_column(int i, int width, int size) const;
private:
	uint8_t _loaded_chunk_distance;

	int _total_chunks_x;
	int _total_chunks_z;

	Terrain* _terrain;
};

#endif
