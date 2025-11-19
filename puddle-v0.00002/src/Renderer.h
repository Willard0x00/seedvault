#ifndef RENDERER_H
#define RENDERER_H

#include <gl/gl3w.h>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "SpriteRenderData.h"

class Shader;
class Entity;

struct SpriteComponent;

enum RendererFlag {
	drawRectNonCenter = 1
};

class Renderer {
public:
	Renderer(Shader* rectShader, Shader* spriteShader, Shader* spriteBatchShader);
	~Renderer();

	void drawRectangle(glm::vec4 rect, glm::vec4 color, int flag = 0) const;

	void drawSprite(const glm::mat4& model, SpriteComponent* sprite) const;

	void drawSpriteData(const SpriteRenderData& p_spriteRenderData) const;

	GLuint loadTexture(const char* file);
private:
	GLuint m_rectVao;
	GLuint m_rectVertexBuffer;
	GLuint m_rectUvBuffer;
	GLuint m_rectIndicesBuffer;

	GLuint m_spriteBatchVao;
	GLuint m_spriteBatchVertexBuffer;
	GLuint m_spriteBatchUvBuffer;
	GLuint m_spriteBatchIndicesBuffer;
	GLuint m_spriteBatchPositionBuffer;
	GLuint m_spriteBatchScaleBuffer;
	GLuint m_spriteBatchRotationBuffer;
	GLuint m_spriteBatchFrameBuffer;
	GLuint m_spriteBatchDepthBuffer;
	GLuint m_spriteBatchHighlightBuffer;

	Shader* m_rectShader;
	Shader* m_spriteShader;
	Shader* m_spriteBatchShader;

	static Renderer* m_myRenderer;
};

#endif