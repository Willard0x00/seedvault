#include "Shader.h"

#include <string>

#include <vector>
#include <sstream>

#include "Log.h"

int conv_shader_type(std::string_view type) {
	int strlen = (type.ends_with("\n")) ? type.size() - 1 : type.size();

	while (type[strlen - 1] == ' ') {
		--strlen;
	}

	if (type.substr(0, strlen).compare("@Vertex") == 0)			return GL_VERTEX_SHADER;
	else if (type.substr(0, strlen).compare("@Fragment") == 0)	return GL_FRAGMENT_SHADER;
	else if (type.substr(0, strlen).compare("@Geometry") == 0)	return GL_GEOMETRY_SHADER;
	else if (type.substr(0, strlen).compare("@Compute") == 0)	return GL_COMPUTE_SHADER;
	else return -1;
}

constexpr const char* conv_shader_type(int type) {
	if (type == GL_VERTEX_SHADER)		 return "Vertex Shader";
	else if (type == GL_FRAGMENT_SHADER) return "Fragment Shader";
	else if (type == GL_GEOMETRY_SHADER) return "Geometry Shader";
	else if (type == GL_COMPUTE_SHADER)  return "Compute Shader";
	else								 return "Invalid Shader";
}

void printWithLineNumbers(const std::string& buffer) {
	std::stringstream ss(buffer);
	std::string line;
	int num = 0;
	while (std::getline(ss, line, '\n')) {
		Log::get().write(L_ERROR, 
			(num < 10) ? "000" : (num < 100) ? "00" : (num < 1000) ? "0" : "",
			num, " | ", line);
		++num;
	}
}

Shader::Shader(const char* path) :
	_id	( glCreateProgram() )
{
	FILE* file;
	if (fopen_s(&file, path, "r") != 0) {
		Log::get().write(L_ERROR, "Error opening shader file at: ", path);
		glDeleteProgram(_id);
		return;
	}

	char chunk[128];
	std::string buffer;
	int type = -1;

	while (fgets(chunk, sizeof(chunk), file) != NULL) {
		if (chunk[0] == '@') {
			std::string temp(chunk);
			if (temp.substr(0, 4) == "@End") {
				int id = glCreateShader(type);

				const GLchar* source = (const GLchar*)buffer.c_str();
				glShaderSource(id, 1, &source, 0);
				glCompileShader(id);

				GLint result = 0;
				GLint logLength = 0;
				glGetShaderiv(id, GL_COMPILE_STATUS, &result);
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);

				Log::get().write((result == GL_TRUE) ? L_INFO : L_ERROR, conv_shader_type(type), " [", path, "] -> ", (result == GL_TRUE) ? "Compiled" : "Failed");
				if (logLength > 0) {
					GLchar* log = new GLchar[logLength];
					glGetShaderInfoLog(id, logLength, 0, log);
					printWithLineNumbers(buffer);
					Log::get().write(L_ERROR, log);
				}

				if (result != GL_TRUE) {
					glDeleteShader(id);
					glDeleteProgram(_id);
					fclose(file);
					return;
				}

				glAttachShader(_id, id);
				glDeleteShader(id);
			}
			else {
				type = conv_shader_type(chunk);

				if (type == -1) {
					Log::get().write(L_ERROR, "Shader has invalid type usage with '@'");
					glDeleteProgram(_id);
					return;
				}
				buffer.clear();
			}
		}
		else {
			buffer.append(chunk);
		}

	}

	glLinkProgram(_id);
	fclose(file);
}

Shader::~Shader() {
	glDeleteProgram(_id);
}

void Shader::use() const {
	glUseProgram(_id);
}

GLint Shader::location(const char* name) const {
	return glGetUniformLocation(_id, name);
}

void Shader::setBool(const char* name, bool b) const {
	glUseProgram(_id);
	glUniform1f(glGetUniformLocation(_id, name), (float)b);
}

void Shader::setInt(const char* name, int i) const {
	glUseProgram(_id);
	glUniform1i(glGetUniformLocation(_id, name), i);
}

void Shader::setFloat(const char* name, float f) const {
	glUseProgram(_id);
	glUniform1f(glGetUniformLocation(_id, name), f);
}

void Shader::setDouble(const char* name, double d) const {
	glUseProgram(_id);
	glUniform1d(glGetUniformLocation(_id, name), d);
}

void Shader::setVec2(const char* name, const glm::vec2& v2) const {
	glUseProgram(_id);
	glUniform2fv(glGetUniformLocation(_id, name), 1, &v2[0]);
}

void Shader::setVec3(const char* name, const glm::vec3& v3) const {
	glUseProgram(_id);
	glUniform3fv(glGetUniformLocation(_id, name), 1, &v3[0]);
}

void Shader::setVec4(const char* name, const glm::vec4& v4) const {
	glUseProgram(_id);
	glUniform4fv(glGetUniformLocation(_id, name), 1, &v4[0]);
}

void Shader::setMat4(const char* name, const glm::mat4& mat4) const {
	glUseProgram(_id);
	glUniformMatrix4fv(glGetUniformLocation(_id, name), 1, GL_FALSE, &mat4[0][0]);
}