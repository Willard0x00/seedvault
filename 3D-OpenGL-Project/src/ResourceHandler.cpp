#include "ResourceHandler.h"

int ResourceHandler::Init() {
	_camera.Init(45.0f, 1100.f, 800.0f, 1.0f, 1000.0f);
	RenderObject o1;
	RenderObject o2("Data/Objects/default.obj", "Data/Objects/Shaders/default.vs", "Data/Objects/Shaders/default.fs", "Data/Objects/Textures/obj2.bmp");
	RenderObject o3("Data/Objects/level.obj", "Data/Objects/Shaders/level.vs", "Data/Objects/Shaders/level.fs");
	load_obj(o1);
	load_obj(o2);
	load_obj(o3);
	return 0;
}

void ResourceHandler::load_obj(RenderObject &obj) {
	load_objFile(obj);
	loadShaders(obj._vertexShaderPath, obj._fragmentShaderPath, obj._program_id);
	_camera._matrix_ids.push_back(glGetUniformLocation(obj._program_id, "MVP"));
	obj._id = _camera._matrix_ids.size() - 1;
	obj._model_id = glGetUniformLocation(obj._program_id, "M");
	if (obj._hasTexture) {
		obj._texture_id = glGetUniformLocation(obj._program_id, "textureSampler");
		loadTexture(obj._texturePath, obj._texture);
	}
	obj._isLoaded = true;
	_renderObjects.push_back(obj);
}

bool ResourceHandler::load_objFile(RenderObject &obj) {
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tempVertices, vertices;
	std::vector<glm::vec2> tempUvs, uvs;
	std::vector<glm::vec3> tempNormals, normals;
	char line[128];
	FILE *file;
	fopen_s(&file, obj._path, "r");
	if (!file) {
		printf("Can not open file: %s\n", obj._path);
		return false;
	}

	while (!feof(file)) {
		fscanf_s(file, "%s", line, _countof(line));
		if (strcmp(line, "v") == 0) {
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
			tempVertices.push_back(vertex);
		}
		else if (strcmp(line, "vt") == 0) {
			glm::vec2 uv;
			fscanf_s(file, "%f %f", &uv.x, &uv.y);
			uv.y = 1.0f - uv.y;
			tempUvs.push_back(uv);
		}
		else if (strcmp(line, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		}
		else if (strcmp(line, "f") == 0) {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			fscanf_s(
				file,
				"%d/%d/%d %d/%d/%d %d/%d/%d",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]
			);
			for (unsigned int i = 0; i < 3; i++) {
				vertexIndices.push_back(vertexIndex[i]);
				uvIndices.push_back(uvIndex[i]);
				normalIndices.push_back(normalIndex[i]);
			}
		}
	}

	fclose(file);

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		vertices.push_back(tempVertices[vertexIndices[i] - 1]);
		uvs.push_back(tempUvs[uvIndices[i] - 1]);
		normals.push_back(tempNormals[normalIndices[i] - 1]);
	}

	index_vbo(
		vertices,
		uvs,
		normals,
		obj._indices,
		obj._vertices,
		obj._uvs,
		obj._normals
	);

	loadBuffers(obj);

	return true;
}

void ResourceHandler::index_vbo(
	std::vector<glm::vec3> &inVertices,
	std::vector<glm::vec2> &inUvs,
	std::vector<glm::vec3> &inNormals,
	std::vector<unsigned short> &indices,
	std::vector<glm::vec3> &outVertices,
	std::vector<glm::vec2> &outUvs,
	std::vector<glm::vec3> &outNormals
) {
	std::map<PackedVertex, unsigned short> vertexToOutIndex;

	for (unsigned int i = 0; i < inVertices.size(); i++) {
		PackedVertex packed = { inVertices[i], inUvs[i], inNormals[i] };
		unsigned short index;
		bool found = getSimilarVertexIndex_fast(packed, vertexToOutIndex, index);

		if (found)
			indices.push_back(index);
		else {
			outVertices.push_back(inVertices[i]);
			outUvs.push_back(inUvs[i]);
			outNormals.push_back(inNormals[i]);
			unsigned short newIndex = (unsigned short)outVertices.size() - 1;
			indices.push_back(newIndex);
			vertexToOutIndex[packed] = newIndex;
		}
	}
}

bool ResourceHandler::getSimilarVertexIndex_fast(
	PackedVertex &packed,
	std::map<PackedVertex, unsigned short> &vertexToOutIndex,
	unsigned short &result
) {
	std::map<PackedVertex, unsigned short>::iterator it = vertexToOutIndex.find(packed);
	if (it == vertexToOutIndex.end())
		return false;
	result = it->second;
	return true;
}

void ResourceHandler::loadBuffers(RenderObject &obj) {
	glGenBuffers(1, &obj._vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, obj._vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, obj._vertices.size() * sizeof(glm::vec3), &obj._vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &obj._uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, obj._uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, obj._uvs.size() * sizeof(glm::vec2), &obj._uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &obj._normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, obj._normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, obj._normals.size() * sizeof(glm::vec3), &obj._normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &obj._elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj._elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj._indices.size() * sizeof(unsigned short), &obj._indices[0], GL_STATIC_DRAW);
}

bool ResourceHandler::loadShaders(const char *vertexShaderPath, const char *fragmentShaderPath, GLuint &program_id) {
	GLuint vertexShader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader_id = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderCode = loadShaderFile(vertexShaderPath);
	std::string fragmentShaderCode = loadShaderFile(fragmentShaderPath);
	if (vertexShaderCode == "" || fragmentShaderCode == "")
		return false;

	if (!compileShader(vertexShader_id, vertexShaderPath, vertexShaderCode) ||
		!compileShader(fragmentShader_id, fragmentShaderPath, fragmentShaderCode))
		return false;

	program_id = glCreateProgram();
	glAttachShader(program_id, vertexShader_id);
	glAttachShader(program_id, fragmentShader_id);
	glLinkProgram(program_id);

	GLint result;
	int infoLogLength;
	glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		printf("Program Linking Error\n");
		std::vector<char> errorMessage(infoLogLength + 1);
		glGetProgramInfoLog(program_id, infoLogLength, NULL, &errorMessage[0]);
		printf("%s\n", &errorMessage[0]);
	}

	glDetachShader(program_id, vertexShader_id);
	glDetachShader(program_id, fragmentShader_id);
	glDeleteShader(vertexShader_id);
	glDeleteShader(fragmentShader_id);

	return true;
}

std::string ResourceHandler::loadShaderFile(const char *path) {
	std::string shaderCode;
	std::ifstream shaderFile(path, std::ios::in);
	if (shaderFile.is_open()) {
		std::stringstream sstr;
		sstr << shaderFile.rdbuf();
		shaderCode = sstr.str();
		shaderFile.close();
		return shaderCode;
	}
	printf("Could not open Shader: %s\n", path);
	return "";
}

bool ResourceHandler::compileShader(GLuint shader_id, const char *path, std::string code) {
	GLint result;
	int infoLogLength;
	printf("Compiling shader: %s\n", path);
	const char *shaderPointer = code.c_str();
	glShaderSource(shader_id, 1, &shaderPointer, NULL);
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> errorMessage(infoLogLength + 1);
		glGetShaderInfoLog(shader_id, infoLogLength, NULL, &errorMessage[0]);
		printf("%s\n", &errorMessage[0]);
		return false;
	}
	return true;
}

bool ResourceHandler::loadTexture(const char *imagePath, GLuint &texture) {
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int size;
	unsigned char *data;

	FILE *file;
	fopen_s(&file, imagePath, "rb");
	if (!file) {
		printf("Texture file can't be opened - %s\n", imagePath);
		return false;
	}

	if (fread(header, 1, 54, file) != 54) {
		printf("%s - Not a bmp file\n", imagePath);
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("%s - Not a bmp file\n", imagePath);
		return false;
	}

	dataPos = *(int*)&(header[0x0A]);
	size	= *(int*)&(header[0x22]);
	width	= *(int*)&(header[0x12]);
	height	= *(int*)&(header[0x16]);

	if (size == 0)
		size = width * height * 3;
	if (dataPos == 0)
		dataPos = 54;

	data = new unsigned char[size];
	fread(data, 1, size, file);
	fclose(file);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	return true;
}