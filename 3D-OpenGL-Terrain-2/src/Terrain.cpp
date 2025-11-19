#include "Terrain.h"

#include "Program.h"

#include <cassert>

#include <iostream>

Terrain::Terrain(uint8_t depth, Program* mesh_program) :
	_mesh				( mesh_program ),
	_loader				( this, depth - 1),
	_loader_started		( false ),
	_width				( 1 + ((depth - 1) * 2) ),
	_length				( _width )
{
	assert(depth >= 1 && depth < 95);

	_chunks.resize(_width * _length);

	for(auto i = 0; i < _chunks.size(); ++i) {
		_chunks.at(i) = new TerrainChunk;
		_chunks.at(i)->_x = i % _width;
		_chunks.at(i)->_z = i / _width;
	}

	std::cout << "----Terrain----\n" <<
		"Width: " << _width << " | Length: " << _length << "\n" <<
		"Size of Chunks: " << (float)(sizeof(TerrainChunk) * _chunks.size()) / 1024.0f << "KB\n";

	_loader.debug_write_base_terrain();
}

Terrain::~Terrain()
{
	stop_chunk_loader();

	for(auto chunk : _chunks) {
		delete chunk;
	}
}

void Terrain::start_chunk_loader(float* x, float* z) {
	if(!_loader_started) {
		_loader_started = true;
		_loader_thread = std::thread(&TerrainLoader::process_chunk_loading, &_loader, &_loader_started, x, z);
	}
}

void Terrain::stop_chunk_loader() {
	if(_loader_started) {
		_loader_started = false;
		_loader_thread.join();
	}
}

void Terrain::draw() {
	for(auto &chunk : _chunks) {
		_mesh.draw(chunk);
	}
}

int Terrain::get_width() const {
	return _width;
}

int Terrain::get_length() const {
	return _length;
}

size_t Terrain::size() const {
	return _chunks.size();
}

std::vector<TerrainChunk*>* Terrain::get_chunks() {
	return &_chunks;
}

void Terrain::print_array() {
	std::cout << "================Chunks=============\n";
	for(int i = 0; i < _chunks.size(); ++i) {
		if(i != 0 && i % ( _width ) == 0) {
			std::cout << "\n";
		}
		std::cout << i << " " << _chunks.at(i)->_x << " " << _chunks.at(i)->_z << " ";
	}
	std::cout << "\n";
}