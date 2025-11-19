#ifndef SPRITE_H
#define SPRITE_H

#include <string_view>

typedef unsigned int GLuint;

class Program;
struct TransformComponent;
struct SpriteComponent;

class Sprite {
public:
	Sprite(std::string_view image_path);

	~Sprite();

	static void init();

	void draw(Program* program, int mode, TransformComponent* transform, SpriteComponent* sprite);

private:
	static GLuint _vao;
	static GLuint _vertex_buffer;
	GLuint _texture;
};

#endif