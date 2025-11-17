#include <vector>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include<iostream>

#ifndef CAMERA_H
#define CAMERA_H

class Camera {
private:
	std::vector<GLuint> _matrix_ids;
	GLuint _matrix_id;

	glm::vec3 _position;
	glm::vec3 _direction;
	glm::vec3 _right;
	glm::mat4 _projection;
	glm::mat4 _view;
	glm::mat4 _model;
	glm::mat4 _mvp;

	float _horizontalAngle, _verticalAngle;
	float _viewSpeed, _moveSpeed;

	friend class ResourceHandler;
public:
	int Init(float fov, float width, float height, float near, float far);
	void update();
	void uniformMatrix(const int &id);

	void look(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up)		{	_view = glm::lookAt(eye, center, up);									}
	void calcHA(const float &time, const float &windowWidthHalf, const float &mouseX)	{	_horizontalAngle += _viewSpeed * time * (windowWidthHalf - mouseX);		}
	void calcVA(const float &time, const float &windowHeightHalf, const float &mouseY)	{	_verticalAngle += _viewSpeed * time * (windowHeightHalf - mouseY);		}
	void applyObjectMatrix(const glm::mat4 &matrix)										{	_mvp = _projection * _view * matrix;								    }
};

#endif