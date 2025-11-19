#ifndef MAP_H
#define MAP_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <functional>
#include <string>

#include "CreateNewMapDialog.h"

typedef std::function<void(const glm::vec4&, const glm::vec4&, int)> DrawRectangleFn;

class Shader;

enum MarkerFlag {
	CENTER,	CORNER
};

class Map {
public:
	Map(int width, int height, Shader* shader, DrawRectangleFn drawRectangleFn);
	~Map();

	void draw(bool p_drawLines = false);

	void drawMarker();

	void setTile(double x, double y, unsigned int id);

	void setMarker(double x, double y, int flag);

	glm::vec2 center(double x, double y);

	glm::vec2 corner(double x, double y);

	void create(CreateNewMapDialog createNewMapDialog);

	void save(const char* p_file);

	void load(const char* p_file);

	uint32_t calculateCRC(int p_width, int p_height, const std::vector<GLushort>& p_tiles) const;

	void reloadTiles();

	const std::string* getMapName() const;

	const std::string* getMapFile() const;
private:
	GLuint m_vao;
	GLuint m_vertexBuffer;
	GLuint m_uvBuffer;
	GLuint m_indicesBuffer;

	int m_width;
	int m_height;

	std::vector<GLushort> m_tiles;
	GLuint m_tileSheet;
	GLuint m_tileBuffer;

	double m_tileUvWidth;
	double m_tileUvHeight;

	double m_tileUvXOffset;
	double m_tileUvYOffset;

	Shader* m_shader;

	glm::vec4 m_marker;

	DrawRectangleFn m_drawRectangleFn;

	std::string m_name;

	std::string m_file;
};

#endif