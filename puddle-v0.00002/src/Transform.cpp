#include "Transform.h"

Transform::Transform(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) :
	m_position ( position ),
	m_scale ( scale ),
	m_rotation ( rotation )
{}

Transform::Transform(const Transform& rhs) :
	m_position ( rhs.m_position ),
	m_scale ( rhs.m_scale ),
	m_rotation ( rhs.m_rotation )
{}

glm::mat4 Transform::getModel() const {
	glm::mat4 model(1);
	model = glm::translate(model, m_position);
	model = glm::scale(model, m_scale);
	model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
	return model;
}