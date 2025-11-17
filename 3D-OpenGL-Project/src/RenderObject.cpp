#include "RenderObject.h"

RenderObject::RenderObject() {
	_path = "Data/Objects/default.obj";
	_vertexShaderPath = "Data/Objects/Shaders/default.vs";
	_fragmentShaderPath = "Data/Objects/Shaders/default.fs";
	_texturePath = "Data/Objects/Textures/default.bmp";
	_model = glm::mat4(1.0f);
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	_vertexBuffer = 0;
	_uvBuffer = 0;
	_normalBuffer = 0;
	_elementBuffer = 0;
	_isLoaded = false;
	_hasTexture = true;
}

RenderObject::RenderObject(const char *path, const char *vs, const char *fs, const char *texturePath) {
	_path = path;
	_vertexShaderPath = vs;
	_fragmentShaderPath = fs;
	_texturePath = texturePath;
	_model = glm::mat4(1.0f);
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	_vertexBuffer = 0;
	_uvBuffer = 0;
	_normalBuffer = 0;
	_elementBuffer = 0;
	_isLoaded = false;
	_hasTexture = true;
}

RenderObject::RenderObject(const char *path, const char *vs, const char *fs) {
	_path = path;
	_vertexShaderPath = vs;
	_fragmentShaderPath = fs;
	_texturePath = "";
	_model = glm::mat4(1.0f);
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	_vertexBuffer = 0;
	_uvBuffer = 0;
	_normalBuffer = 0;
	_elementBuffer = 0;
	_isLoaded = false;
	_hasTexture = false;
}

void RenderObject::update() {
	_model = glm::mat4(1.0f);
	_model = glm::translate(_model, _position);
	_model = glm::scale(_model, _scale);
}