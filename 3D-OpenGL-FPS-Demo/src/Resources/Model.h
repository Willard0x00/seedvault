#ifndef MODEL_H
#define MODEL_H

#include <string_view>
#include <memory>

#include "Mesh.h"

class Model {
public:
	Model();
	Model(const GLuint program, const std::string_view directory, const std::string_view model_file);
	Model(const size_t id, std::string_view file_path);
	Model(const Model& rhs);

	void draw(Transform& transform);

	std::vector<std::shared_ptr<Mesh>> _meshes;

	GLuint get_program();
private:
	size_t _id;
	GLuint _program;
};

#endif