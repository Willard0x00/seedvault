#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/gtc/matrix_transform.hpp>

struct Transform {
public:
	Transform(
		glm::vec3 position = glm::vec3(0, 0, 0),
		glm::vec3 scale = glm::vec3(1, 1, 1),
		glm::vec3 rotation = glm::vec3(0, 0, 0)
	);

	Transform(const Transform& rhs);

	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_rotation;

	glm::mat4 getModel() const;
private:
};

#endif