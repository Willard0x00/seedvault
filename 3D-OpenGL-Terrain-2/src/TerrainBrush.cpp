#include "TerrainBrush.h"

#include "Program.h"
#include "Collision.h"

TerrainBrush::TerrainBrush(Program* program) :
    _program        ( program ),
    _radius         ( 5.0f ),
    _raise          ( 1.0f )
{}

TerrainBrush::~TerrainBrush() {}

void TerrainBrush::draw() {
    glUseProgram(_program->_id);

    glLineWidth(2);

    glUniform3fv(glGetUniformLocation(_program->_id, "position"), 1, &_position[0]);
    glUniform1f(glGetUniformLocation(_program->_id, "radius"), _radius);

    glDrawArrays(GL_POINTS, 0, 1);

    glLineWidth(1);
}

void TerrainBrush::update(glm::vec3 mouse_vector, glm::vec3 offset) {
    float y = abs(( offset.y - 0 ) / glm::clamp(mouse_vector.y, -1.0f, 0.0f));
    float x = ( y * mouse_vector.x + offset.x );
    float z = ( y * mouse_vector.z + offset.z );

    _position = glm::vec3(x, 0, z);
}

#include <iostream>
void TerrainBrush::raise(TerrainChunks* chunks) {
    glm::vec2 distance = glm::vec2(0, 0);
    short row_begin = short(floor(_position.x - _radius));
    short column_begin = short(floor(_position.z - _radius));
    std::vector<ChunkIndexXZPair> indices;

    for(short x = row_begin; x < row_begin + 2 * _radius; ++x) {
        distance.x = x - _position.x;
        for(short z = column_begin; z < column_begin + 2 * _radius; ++z) {
            distance.y = z - _position.z;
            float length = glm::length(distance);
            float normalized_length = (1.0f - abs(length / _radius));
            if(length <= _radius) {
                indices.push_back({ x, z, normalized_length });
            }
        }
    }

    for(auto chunk : *chunks) {
        int x = chunk->_x * CHUNK_WIDTH;
        int z = chunk->_z * CHUNK_LENGTH;
        glm::vec4 rect = { x, z, x + CHUNK_WIDTH, z + CHUNK_LENGTH };
        glm::vec2 point = { _position.x, _position.z };
        if(collision::circle_and_rect(rect, point, _radius)) {
            for(auto index : indices) {
                chunk->raise(index.x, index.z, _raise, index.normalized_length);
            }
            chunk->calc_normals();
        }
    }
}