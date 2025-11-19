#ifndef ANIMATION_INTERPOLATOR_H
#define ANIMATION_INTERPOLATOR_H

#include "Animation.h"

class AnimationInterpolator {
public:
	AnimationInterpolator(Animation* animation, Frame* frame);
	~AnimationInterpolator();

	void start();

	void update();

	void set(Animation* animation, Frame* frame);

	bool isStopped() const;

	void setDirection(glm::vec3 direction);
private:
	Animation* m_animation;

	Frame* m_frame;

	__int64 m_startTime;

	bool m_stopped;

	glm::vec3 m_direction;
};

#endif