#ifndef ANIMATION_H
#define ANIMATION_H

#include <cstdint>

#include <string>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

enum class AnimationKey {
	NONE,
	IDLE,
	ATTACK
};

constexpr uint8_t g_aniNameToKey(std::string name) {
	if (name == "idle") return 1;
	else if (name == "Attack") return 2;
	return 0;
}

struct Frame {

	void operator=(const Frame& other) {
		m_frame = other.m_frame;
		m_scale = other.m_scale;
		m_rotation = other.m_rotation;
		m_duration = other.m_duration;
		m_durationSum = other.m_durationSum;
	}

	uint16_t m_frame = 0;
	glm::vec3 m_position = glm::vec3(0, 0, 0);
	glm::vec2 m_scale = glm::vec2(1, 1);
	float m_rotation = 0.0f;
	__int64 m_duration = 0;
	__int64 m_durationSum = 0;
};

struct Animation {
	uint8_t m_type = 0;
	std::vector<Frame> m_frames;
	__int64 m_totalDuration = 0;
	bool m_stop = false;
};
 
#endif