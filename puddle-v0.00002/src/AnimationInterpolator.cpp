#include "AnimationInterpolator.h"

#include "EngineClock.h"

#include "Log.h"

AnimationInterpolator::AnimationInterpolator(Animation* p_animation, Frame* p_frame) :
	m_animation ( p_animation ),
	m_frame ( p_frame ),
	m_startTime ( 0 ),
	m_stopped ( false ),
	m_direction ( 1, 1, 1 )
{}

AnimationInterpolator::~AnimationInterpolator()
{}

void AnimationInterpolator::start() {
	m_startTime = EngineClock::get().getCurrentTimeMs();
	m_stopped = false;
}

void AnimationInterpolator::update() {
	if (m_stopped || m_animation->m_frames.size() == 0 || m_animation->m_totalDuration == 0) {
		return;
	}

	__int64 delta = (EngineClock::get().getCurrentTimeMs() - m_startTime) / 1000;

	if (m_animation->m_stop && delta > m_animation->m_totalDuration) {
		m_frame->m_position = m_animation->m_frames[0].m_position;
		m_frame->m_scale = m_animation->m_frames[0].m_scale;
		m_frame->m_rotation = m_animation->m_frames[0].m_rotation;
		m_frame->m_frame = m_animation->m_frames[0].m_frame;
		m_stopped = true;
		return;
	}

	auto& frames = m_animation->m_frames;
	int frameIndex = 0;
	__int64 time = delta % m_animation->m_totalDuration;

	while (frameIndex < frames.size()) {
		if (time <= frames[++frameIndex].m_durationSum) {
			break;
		}
	}

	if (frameIndex == 0) {
		return;
	}

	// interpolate

	auto& to = frames[frameIndex];
	auto& from = frames[frameIndex - 1];
	__int64 length = to.m_durationSum - from.m_durationSum;
	if (length == 0LL) {
		return;
	}
	float interpolation = 1.0f - ((to.m_durationSum - time) / (float)length);
	m_frame->m_position = glm::mix(from.m_position, to.m_position, interpolation) * m_direction;
	m_frame->m_scale = glm::mix(from.m_scale, to.m_scale, interpolation);
	m_frame->m_rotation = glm::mix(from.m_rotation, to.m_rotation, interpolation);
	m_frame->m_duration = time;
	m_frame->m_frame = from.m_frame;
}

void AnimationInterpolator::set(Animation* p_animation, Frame* p_frame) {
	m_animation = p_animation;
	m_frame = p_frame;
}

bool AnimationInterpolator::isStopped() const {
	return m_stopped;
}

void AnimationInterpolator::setDirection(glm::vec3 direction) {
	m_direction = direction;
}