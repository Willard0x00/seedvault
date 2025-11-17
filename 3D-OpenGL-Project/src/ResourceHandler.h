#include <vector>

#include "RenderObject.h"
#include "Camera.h"

#ifndef RESOURCE_HANDLER_H
#define RESOURCE_HANDLER_H

struct PackedVertex {
	glm::vec3 vertex;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex packed) const { return memcmp((void*)this, (void*)&packed, sizeof(PackedVertex)) > 0; }
};

class ResourceHandler {
private:
	std::vector<RenderObject> _renderObjects;
	Camera _camera;
	friend class Renderer;
public:
	int Init();

	void load_obj(RenderObject &obj);
	void index_vbo(
		std::vector<glm::vec3> &inVertices,
		std::vector<glm::vec2> &inUvs,
		std::vector<glm::vec3> &inNormals,
		std::vector<unsigned short> &indices,
		std::vector<glm::vec3> &outVertices,
		std::vector<glm::vec2> &outUvs,
		std::vector<glm::vec3> &outNormals
	);
	void loadBuffers(RenderObject &obj);
	bool load_objFile(RenderObject &obj);
	bool getSimilarVertexIndex_fast(
		PackedVertex &packed,
		std::map<PackedVertex, unsigned short> &vertexToOutIndex,
		unsigned short &result 
	);
	bool loadShaders(const char *vertexShaderPath, const char *fragmentShaderPath, GLuint &program_id);
	bool compileShader(GLuint shader, const char *path, std::string code);
	bool loadTexture(const char *imagePath, GLuint &texture_id);

	std::string loadShaderFile(const char *path);

	void updateCamera() { _camera.update(); }
	void updateCameraAngles(const double &time,	const int &widthHalf, const int &heightHalf, const double &mouseX, const double &mouseY) 
		{	_camera.calcHA((float)time, (float)widthHalf, (float)mouseX);	_camera.calcVA((float)time, (float)heightHalf, (float)mouseY);	}
	 
	// FREE LOOKING 
	/*
	void updateCameraUp    (const double &time)		{	_camera._position += _camera._direction * (float)time * _camera._moveSpeed;	  	 }
	void updateCameraDown  (const double &time)		{   _camera._position -= _camera._direction * (float)time * _camera._moveSpeed;		 }
	void updateCameraRight (const double &time)		{   _camera._position += _camera._right     * (float)time * _camera._moveSpeed;		 }
	void updateCameraLeft  (const double &time)		{   _camera._position -= _camera._right     * (float)time * _camera._moveSpeed;		 }
	*/

	// FPS STYLE

	void updateCameraUp(const double &time) { 
		_camera._position.z += _camera._direction.z * (float)time * _camera._moveSpeed;
		_camera._position.x += _camera._direction.x * (float)time * _camera._moveSpeed; 
	}

	void updateCameraDown(const double &time) {
		_camera._position.z -= _camera._direction.z * (float)time * _camera._moveSpeed;
		_camera._position.x -= _camera._direction.x * (float)time * _camera._moveSpeed;
	}

	void updateCameraRight(const double &time) {
		_camera._position.x += _camera._right.x * (float)time * _camera._moveSpeed;
		_camera._position.z += _camera._right.z * (float)time * _camera._moveSpeed;
	}

	void updateCameraLeft(const double &time) {
		_camera._position.x -= _camera._right.x * (float)time * _camera._moveSpeed;
		_camera._position.z -= _camera._right.z * (float)time * _camera._moveSpeed;
	}
	
	void updateObjects()   { for (unsigned int i = 0; i < _renderObjects.size(); i++) _renderObjects[i].update(); }

	void updateObjectUp    (const double &time, const int &id)		{    _renderObjects[id]._position.y += 0.5f * (float)time;	 }
	void updateObjectDown  (const double &time, const int &id)		{	 _renderObjects[id]._position.y -= 0.5f * (float)time;	 }
	void updateObjectRight (const double &time, const int &id)		{	 _renderObjects[id]._position.x += 0.5f * (float)time;	 }
	void updateObjectLeft  (const double &time, const int &id)		{	 _renderObjects[id]._position.x -= 0.5f * (float)time;   }

	void updateObjectScale (const float &factor, const int &id)		{	 _renderObjects[id].scale(factor);						 }
};  

#endif