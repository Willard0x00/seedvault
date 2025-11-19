#include "Sprite.h"

#include <GL/gl3w.h>

#include <SOIL/SOIL2.h>

#include "Program.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

static bool initialized = false;

GLuint Sprite::_vao = 0;
GLuint Sprite::_vertex_buffer = 0;

const static float vertices[] = {
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
};

Sprite::Sprite(std::string_view image_path) :
       _texture        ( 0 ) 
{
    if (!initialized) {
        init();
    }

    _texture = SOIL_load_OGL_texture(image_path.data(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if (_texture == 0) {
        printf("error loading texture: %s", image_path.data());
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Sprite::~Sprite() {
}

void Sprite::init() {
    glCreateVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glCreateBuffers(1, &_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
    glNamedBufferStorage(_vertex_buffer, sizeof(float) * 2 * 6, &vertices[0], 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Sprite::draw(Program* program, int mode, TransformComponent* transform, SpriteComponent* sprite) {
    glBindVertexArray(_vao);
    program->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glUniformMatrix4fv(program->location("model"), 1, GL_FALSE, &transform->get_model()[0][0]);
    glUniform1i(program->location("frame"), sprite->_frame);

    glDrawArrays(mode, 0, 6);
}