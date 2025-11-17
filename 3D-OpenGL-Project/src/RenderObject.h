#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

class RenderObject {
private:
	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec2> _uvs;
	std::vector<glm::vec3> _normals;
	std::vector<unsigned short> _indices;
	glm::mat4 _model;
	glm::vec3 _position;
	glm::vec3 _scale;
	GLuint _vertexBuffer;
	GLuint _uvBuffer;
	GLuint _normalBuffer;
	GLuint _elementBuffer;
	GLuint _program_id;
	GLuint _model_id;
	GLuint _texture_id;
	GLuint _texture;
	const char *_path;
	const char *_vertexShaderPath;
	const char *_fragmentShaderPath;
	const char *_texturePath;

	bool _isLoaded;
	bool _hasTexture;

	int _id;

	friend class Renderer;
	friend class ResourceHandler;
public:
	RenderObject();
	RenderObject(const char *path, const char *vs, const char *fs, const char *texturePath);
	RenderObject(const char *path, const char *vs, const char *fs);
	void update();
	void scale(const float &factor) { _scale.x *= factor; _scale.y *= factor; _scale.z *= factor; }
};

#endif