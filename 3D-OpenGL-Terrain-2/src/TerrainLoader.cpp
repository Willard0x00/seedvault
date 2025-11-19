#include "TerrainLoader.h"

#include "Terrainchunk.h"
#include "Terrain.h"

#include <string>
#include <iostream>
#include <cassert>

#define FORWARD 0x01
#define REVERSE 0x02

TerrainLoader::TerrainLoader(Terrain* terrain, uint8_t loaded_chunk_distance) :
	_terrain					( terrain ),
	_loaded_chunk_distance		( loaded_chunk_distance ),
	_total_chunks_x				( 100 ),
	_total_chunks_z				( 100 )
{}

void TerrainLoader::process_chunk_loading(bool* started, float* camera_x, float* camera_z) {
	while(*started) {
		int x = int(*camera_x / float(CHUNK_WIDTH));
		int z = int(*camera_z / float(CHUNK_LENGTH));

		if(( max_x() - x ) < _loaded_chunk_distance) {
			load_terrain_column(FORWARD);
		}

		if(( x - min_x() ) < _loaded_chunk_distance) {
			load_terrain_column(REVERSE);
		}

		if(( max_z() - z ) < _loaded_chunk_distance) {
			load_terrain_row(FORWARD);
		}

		if(( z - min_z() ) < _loaded_chunk_distance) {
			load_terrain_row(REVERSE);
		}
	}
}

void TerrainLoader::debug_write_base_terrain() {
	std::fstream file(TERRAIN_FILE, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
	std::vector<TerrainChunk> row;
	row.resize(_total_chunks_x);
	float bytes = 0;
	for(int z = 0; z < _total_chunks_z; ++z) {
		for(int x = 0; x < _total_chunks_x; ++x) {
			row[x]._x = x;
			row[x]._z = z;
		}

		file.write(reinterpret_cast<char*>(&row[0]), row.size() * sizeof(TerrainChunk));
		std::cout << "\r    [" << ( z / (float)_total_chunks_z ) * 100
			<< "%] Generating Terrain...";
		bytes += row.size() * sizeof(TerrainChunk);
	}
	std::cout << "\n    [100%] Generated " << TERRAIN_FILE << " " 
			  << _total_chunks_x << "x" << _total_chunks_z
			  << " " << bytes / (1024.0f * 1024.0f) << "MB\n";
}

void TerrainLoader::load_terrain_column(uint8_t direction) {
	TerrainChunk* old_chunk = nullptr;
	auto chunks = _terrain->get_chunks();
	auto width = _terrain->get_width();

	if(direction & FORWARD && (max_x() < _total_chunks_x - 1)) {
		int i = 0;
		while(i < chunks->size()) {
			chunks->at(i)->save(_total_chunks_x);
			if(is_first_index_in_row(i, width)) {
				old_chunk = chunks->at(i);
				chunks->at(i) = chunks->at(i + 1);
			}
			else if(is_last_index_in_row(i, width)) {
				assert(old_chunk);
				int new_index = new_chunk_index(chunks->at(i), 1, 0);
				old_chunk->read(new_index);
				chunks->at(i) = old_chunk;
			}
			else {
				chunks->at(i) = chunks->at(i + 1);
			}

			++i;
		}
	}
	else if(direction & REVERSE && (min_x() > 0)) {
		int i = chunks->size() - 1;
		while(i >= 0) {
			chunks->at(i)->save(_total_chunks_x);
			if(is_last_index_in_row(i, width)) {
				old_chunk = chunks->at(i);
				chunks->at(i) = chunks->at(i - 1);
			}
			else if(is_first_index_in_row(i, width)) {
				assert(old_chunk);
				int new_index = new_chunk_index(chunks->at(i), -1, 0);
				old_chunk->read(new_index);
				chunks->at(i) = old_chunk;
			}
			else {
				chunks->at(i) = chunks->at(i - 1);
			}

			--i;
		}
	}
}

void TerrainLoader::load_terrain_row(uint8_t direction) {
	TerrainChunk* old_chunk = nullptr;
	auto chunks = _terrain->get_chunks();
	auto width = _terrain->get_width();

	if(direction & FORWARD && (max_z() < _total_chunks_z - 1)) {
		int i = 0;
		while(i < chunks->size()) {
			chunks->at(i)->save(_total_chunks_x);
			if(is_first_index_in_column(i, width)) {
				old_chunk = chunks->at(i);
				chunks->at(i) = chunks->at(i + width);
			}
			else if(is_last_index_in_column(i, width, chunks->size())) {
				assert(old_chunk);
				int new_index = new_chunk_index(chunks->at(i), 0, 1);
				old_chunk->read(new_index);
				chunks->at(i) = old_chunk;
			}
			else {
				chunks->at(i) = chunks->at(i + width);
			}

			i = iterate_on_column(i, width, chunks->size());
		}
	}
	else if(direction & REVERSE && (min_z() > 0)) {
		for(auto c : *chunks) {
			c->save(_total_chunks_x);
		}
		int i = chunks->size() - 1;
		while(i >= 0) {
			chunks->at(i)->save(_total_chunks_x);
			if(is_last_index_in_column(i, width, chunks->size())) {
				old_chunk = chunks->at(i);
				chunks->at(i) = chunks->at(i - width);
			}
			else if(is_first_index_in_column(i, width)) {
				assert(old_chunk);
				int new_index = new_chunk_index(chunks->at(i), 0, -1);
				old_chunk->read(new_index);
				chunks->at(i) = old_chunk;
			}
			else {
				chunks->at(i) = chunks->at(i - width);
			}

			i = riterate_on_column(i, width, chunks->size());
		}

	}
}

int TerrainLoader::iterate_on_column(int i, int width, int size) const {
	return ( i + width >= size && i + width != size - 1 + width) ? i + width - size + 1 : i + width;
}

int TerrainLoader::riterate_on_column(int i, int width, int size) const {
	return ( i - width < 0 && i - width != -width ) ? i - width + size - 1 : i - width;
}

int TerrainLoader::new_chunk_index(TerrainChunk* chunk, int x_offset, int z_offset) const {
    auto x = chunk->_x + x_offset;
    auto z = chunk->_z + z_offset;
    return x + z * _total_chunks_x;
}

bool TerrainLoader::is_first_index_in_row(int index, int width) const {
    return ( index % width == 0 );
}

bool TerrainLoader::is_last_index_in_row(int index, int width) const {
    return ( index != 0 && ( index % width ) == ( width - 1 ));
}

bool TerrainLoader::is_first_index_in_column(int index, int width) const {
	return ( index < width );
}

bool TerrainLoader::is_last_index_in_column(int index, int width, int size) const {
	return ( index >= size - width );
}

int TerrainLoader::min_x() const {
	return _terrain->get_chunks()->at(0)->_x;
}

int TerrainLoader::max_x() const {
	return _terrain->get_chunks()->at(_terrain->get_width() - 1)->_x;
}

int TerrainLoader::min_z() const {
	return _terrain->get_chunks()->at(0)->_z;
}

int TerrainLoader::max_z() const {
	return _terrain->get_chunks()->at(_terrain->get_chunks()->size() - 1)->_z;
}