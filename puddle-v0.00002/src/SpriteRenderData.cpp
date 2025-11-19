#include "SpriteRenderData.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Entity.h"

constexpr bool g_enableCulling = true;

/*
std::vector<TransformComponent*> g_leftArray(3000);
std::vector<TransformComponent*> g_rightArray(3000);

void merge(std::vector<TransformComponent*>& p_array, const int p_left, const int p_mid, const int p_right) {
	const int subArrayOne = p_mid - p_left + 1;
	const int subArrayTwo = p_right - p_mid;

	if (g_leftArray.size() < subArrayOne) {
		g_leftArray.resize(subArrayOne);
	}

	if (g_rightArray.size() < subArrayTwo) {
		g_rightArray.resize(subArrayTwo);
	}
	
	memcpy(&g_leftArray[0], &p_array[p_left], subArrayOne * sizeof(TransformComponent*));
	memcpy(&g_rightArray[0], &p_array[p_mid + 1], subArrayTwo * sizeof(TransformComponent*));

	int indexOfSubArrayOne = 0;
	int indexOfSubArrayTwo = 0;
	int indexOfMergedArray = p_left;

	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (g_leftArray[indexOfSubArrayOne]->m_position.y + g_leftArray[indexOfSubArrayOne]->m_height / 2 <= g_rightArray[indexOfSubArrayTwo]->m_position.y + g_rightArray[indexOfSubArrayTwo]->m_height / 2) {
			p_array[indexOfMergedArray] = g_leftArray[indexOfSubArrayOne];
			++indexOfSubArrayOne;
		}
		else {
			p_array[indexOfMergedArray] = g_rightArray[indexOfSubArrayTwo];
			++indexOfSubArrayTwo;
		}
		++indexOfMergedArray;
	}

	while (indexOfSubArrayOne < subArrayOne) {
		p_array[indexOfMergedArray] = g_leftArray[indexOfSubArrayOne];
		++indexOfSubArrayOne;
		++indexOfMergedArray;
	}

	while (indexOfSubArrayTwo < subArrayTwo) {
		p_array[indexOfMergedArray] = g_rightArray[indexOfSubArrayTwo];
		++indexOfSubArrayTwo;
		++indexOfMergedArray;
	}
}

void SpriteRenderData::mergeSort(std::vector<TransformComponent*>& p_array, const int p_begin, const int p_end) {
	if (p_begin >= p_end) {
		return;
	}

	int mid = p_begin + (p_end - p_begin) / 2;
	mergeSort(p_array, p_begin, mid);
	mergeSort(p_array, mid + 1, p_end);
	merge(p_array, p_begin, mid, p_end);
}

*/

SpriteRenderData::SpriteRenderData()
{}

SpriteRenderData::~SpriteRenderData()
{}

void SpriteRenderData::send(const std::vector<TransformComponent*>& p_transforms, glm::vec4 viewport) {
	m_renderData.clear();

	for (int i = 0; i < p_transforms.size(); ++i) {
		const auto transform = p_transforms[i];
		const auto entity = p_transforms[i]->m_entity;

		if (const auto sprite = entity->get<SpriteComponent>()) {
			if (sprite->m_isVisible && g_enableCulling && !transform->collidesWith(viewport, false)) {
				continue;
			}

			auto& data = m_renderData[sprite->m_sprite->getId()];
			data.m_frameBuffer.push_back(sprite->m_frame.m_frame);

			data.m_positionBuffer.push_back(transform->m_position + sprite->m_frame.m_position);

			data.m_scaleBuffer.push_back(transform->m_scale * sprite->m_frame.m_scale);

			data.m_rotationBuffer.push_back(transform->m_rotation + sprite->m_frame.m_rotation);

			data.m_highlights.push_back((float)sprite->m_highlight);

			data.m_depths.push_back(transform->m_position.y + (transform->m_height * transform->m_scale.y / 2));

			++data.m_instances;
			data.m_sprite = sprite->m_sprite;
		}
	}

}

const std::map<unsigned int, SpriteRenderData::Data>& SpriteRenderData::get() const {
	return m_renderData;
}