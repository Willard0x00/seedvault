#include "Camera.h"

#include <glm/glm.hpp>

int Camera::Init(float fov, float width, float height, float p_near, float p_far) {
	_horizontalAngle = 3.14f;
	_verticalAngle = 0.0f;
	_viewSpeed = 0.5f;
	_moveSpeed = 15.0f;
	_position = glm::vec3(0.0f, 0.5f, 5.0f);
	_projection = glm::perspective(glm::radians(fov), width / height, p_near, p_far);
	_view = glm::lookAt(glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	_model = glm::mat4(1.0f);
	_mvp = _projection * _view * _model;
	return 0;
}

void Camera::update() {
	if (_position.y > 0.5) {
		_position -= 0.0001;
		if (_position.y < 0.5) {
			_position.y = 0.5;
		}
	}



	_direction = glm::vec3(
		cos(_verticalAngle) * sin(_horizontalAngle),
		sin(_verticalAngle),
		cos(_verticalAngle) * cos(_horizontalAngle)
	);
	_right = glm::vec3(
		sin(_horizontalAngle - 3.14f / 2.0f),
		0,
		cos(_horizontalAngle - 3.14f / 2.0f)
	);
	glm::vec3 up = glm::cross(_right, _direction);

	look(
		_position,
		_position + _direction,
		up
	);

	_mvp = _projection * _view * _model;

	for (unsigned int i = 0; i < _matrix_ids.size(); i++) {
		glUniformMatrix4fv(_matrix_ids[i], 1, GL_FALSE, &_mvp[0][0]);
	}

	glUniformMatrix4fv(_matrix_id, 1, GL_FALSE, &_mvp[0][0]);

}

void Camera::uniformMatrix(const int& id) {
	glUniformMatrix4fv(_matrix_ids[id], 1, GL_FALSE, &_mvp[0][0]);
}