#ifndef SPRITE_H
#define SPRITE_H

#include "Animation.h"

#include <rapidjson/document.h>

#include <GL/gl3w.h>

#include <cstdint>
#include <vector>
#include <map>

class Sprite {
public:
	Sprite(const char* path);
	~Sprite();

	uint16_t getId() const;

	GLuint getTexture() const;

	Animation* const getAnimation(uint8_t key);

	uint16_t getSpriteWidth() const;

	uint16_t getSpriteHeight() const;

	uint16_t getImgWidth() const;
	
	uint16_t getImgHeight() const;

	double getSpriteUvWidth() const;

	double getSpriteUvHeight() const;

	double getSpriteUvXOffset() const;

	double getSpriteUvYOffset() const;

	int getSpriteSize() const;

	const uint8_t* getAlphaMask(int frame) const;

	void generateAlphaMasks();
private:
	uint16_t m_id;

	GLuint m_texture;

	std::map<uint8_t, Animation> m_animations;

	uint16_t m_spriteWidth;

	uint16_t m_spriteHeight;

	GLint m_imgWidth;

	GLint m_imgHeight;

	double m_spriteUvWidth;

	double m_spriteUvHeight;

	double m_spriteUvXOffset;

	double m_spriteUvYOffset;

	int m_spriteSize;

	uint16_t m_frames;

	std::vector<uint8_t*> m_alphaMasks;
};

#endif