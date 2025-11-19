#ifndef SPRITE_RENDER_DATA_H
#define SPRITE_RENDER_DATA_H

#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <map>

#include "Sprite.h"

struct SpriteComponent;
struct TransformComponent;

class SpriteRenderData {
public:
	struct Data {
		// one for each entity
		std::vector<glm::vec3> m_positionBuffer;

		std::vector<glm::vec2> m_scaleBuffer;

		std::vector<float> m_rotationBuffer;

		std::vector<float> m_frameBuffer;

		std::vector<float> m_highlights;

		std::vector<float> m_depths;

		// one for each unique sprite image
		unsigned int m_instances =  0;

		Sprite* m_sprite = nullptr;
	};

	SpriteRenderData();
	~SpriteRenderData();

	void send(const std::vector<TransformComponent*>& p_transforms, glm::vec4 viewport);

	// not used delete this later
	//static void mergeSort(std::vector<TransformComponent*>& p_array, const int p_begin, const int p_end);

	const std::map<unsigned int, Data>& get() const;
private:
	std::map<unsigned int, Data> m_renderData;
};

#endif