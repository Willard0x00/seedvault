#include "TerrainChunk.h"

#include <fstream>

void TerrainChunk::raise(unsigned short x, unsigned short z, float val, float normalized_length) {
    int bounds[4] = { _x       * CHUNK_WIDTH,
                    ( _x + 1 ) * CHUNK_WIDTH,
                      _z       * CHUNK_LENGTH,
                    ( _z + 1 ) * CHUNK_LENGTH };


    if(x >= bounds[0] && x <= bounds[1] && z >= bounds[2] && z <= bounds[3]) {
      (x < bounds[1]) ? x = x % CHUNK_WIDTH  : x = CHUNK_WIDTH;
      (z < bounds[3]) ? z = z % CHUNK_LENGTH : z = CHUNK_LENGTH;

        int index = x + z * ( MESHES_PER_CHUNK_X + 1 );
        if(index >= 0 && index < _heights.size()) {
            _heights[index] += val * normalized_length;
        }
    }
}

FaceNormal TerrainChunk::calc_face_normal(int index) const {
    if(index < 0 || index + MESHES_PER_CHUNK_X * 2 >= CHUNK_VERTICES)
        return FaceNormal();

    auto a1 = glm::vec3(0, _heights[index + MESHES_PER_CHUNK_X + 1], 1);
    auto b1 = glm::vec3(0, _heights[index], 0);
    auto c1 = glm::vec3(1, _heights[index + 1], 0);
    auto a2 = a1;
    auto b2 = glm::vec3(1, _heights[index + MESHES_PER_CHUNK_X + 2], 1);
    auto c2 = c1;

    FaceNormal face_normal = {
        glm::cross(b1 - c1, a1 - c1),
        glm::cross(b2 - a1, c2 - a2)
    };

    return face_normal;
}

glm::vec3 TerrainChunk::calc_normal(int index) {
    glm::vec3 normal;

    if(index != 0 && ( index + 1 ) % MESHES_PER_CHUNK_X == 0) {
        auto n1 = calc_face_normal(index);
        auto n2 = calc_face_normal(index - MESHES_PER_CHUNK_X);
        auto n3 = calc_face_normal(index - MESHES_PER_CHUNK_X - 1);
        auto n4 = calc_face_normal(index - 1);
        normal = n1.first + n2.first + n2.second + n3.first + n4.first + n4.second;
        return normal;
    }
    else if(index % MESHES_PER_CHUNK_X == 0) {
        auto n1 = calc_face_normal(index);
        auto n2 = calc_face_normal(index - MESHES_PER_CHUNK_X);
        normal = n1.first + n1.second + n2.second;
        return normal;
    }
    else {
        auto n1 = calc_face_normal(index);
        auto n2 = calc_face_normal(index - MESHES_PER_CHUNK_X);
        normal = n1.first + n2.first + n2.second;
        return normal;
    }
}

void TerrainChunk::calc_normals() {
    for(int i = 0; i < _normals.size(); ++i) {
        _normals[i] = calc_normal(i);
    }
}

bool TerrainChunk::read(int index) {
    std::fstream file(TERRAIN_FILE, std::ios::in | std::ios::binary);

    if(file.is_open()) {
        int offset = index * sizeof(TerrainChunk);
        file.seekg(offset, std::ios::beg);

        auto chunk_ptr = reinterpret_cast<char*>( this );
        auto size = sizeof(TerrainChunk);
        file.read(chunk_ptr, size);
        return true;
    }

    return false;
}

bool TerrainChunk::save(int total_chunks_x) const {
    std::fstream file(TERRAIN_FILE, std::ios::in | std::ios::out | std::ios::binary);

    if(file.is_open()) {
        int offset = (_x + _z * total_chunks_x) * sizeof(TerrainChunk);

        file.seekg(offset, std::ios::beg);
        auto chunk_ptr = reinterpret_cast<const char*>( this );
        auto size = sizeof(TerrainChunk);

        file.write(chunk_ptr, size);

        return true;
    }

    return false;
}