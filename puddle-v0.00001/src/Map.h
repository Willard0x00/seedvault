#ifndef MAP_H
#define MAP_H

#include <GL/gl3w.h>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include <string>

typedef unsigned int GLuint;
class Program;

class Map {
public:
	Map();
	~Map();

	static void init();

	void draw(Program* program, int mode);

	void setTile(double x, double y, GLushort tile);

	void reloadTiles();

	void save(std::string_view path = "");

	void load(std::string_view path);

	uint32_t calculateCrc() const;
private:
	int m_width;
	int m_height;

	static GLuint m_vao;
	static GLuint m_vertexBuffer;
	
	GLuint m_tileBuffer;
	glm::vec2 m_tileSize;

	std::vector<GLushort> m_tiles;
	GLuint m_tileSheet;

	std::string m_file;
};

#endif
