#ifndef TERRAIN_BRUSH_H
#define TERRAIN_BRUSH_H

#include <GL/gl3w.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Terrain.h"

struct Program;

struct ChunkIndexXZPair {
    short x;
    short z;
    float normalized_length;
};

class TerrainBrush {
public:
    TerrainBrush(Program* program);
    ~TerrainBrush();

    void draw();

    void update(glm::vec3 mouse_vector, glm::vec3 offset);

    void raise(TerrainChunks* chunks);
private:
    glm::vec3 _position;
    GLfloat _radius;
    GLfloat _raise;

    Program* _program;
};

#endif