#ifndef Shader_H
#define Shader_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <string>

class Shader {
public:
	Shader(const char* path);

	~Shader();

	void use() const;

	GLint location(const char* name) const;

	void setBool(const char* name, bool b) const;
	void setInt(const char* name, int i) const;
	void setFloat(const char* name, float f) const;
	void setDouble(const char* name, double d) const;
	void setVec2(const char* name, const glm::vec2& v2) const;
	void setVec3(const char* name, const glm::vec3& v3) const;
	void setVec4(const char* name, const glm::vec4& v4) const;
	void setMat4(const char* name, const glm::mat4& mat4) const;
private:
	GLuint _id;
};

#endif