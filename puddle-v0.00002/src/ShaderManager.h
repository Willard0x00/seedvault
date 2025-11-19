#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include <string>
#include <memory>

class Shader;

class ShaderManager {
public:
	ShaderManager();
	~ShaderManager();

	Shader* getShader(const std::string& name) const;

	void updateGlobalUniformMat4(const char* name, const glm::mat4& mat4);
private:
	std::map<std::string, std::unique_ptr<Shader>> m_shaders;
};

#endif