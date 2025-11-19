#include "Map.h"

#include <SOIL/SOIL2.h>

#include "Log.h"
#include "Shader.h"

#define CRCPP_BRANCHLESS
#define CRCPP_USE_CPP11
#include "CRC.h"

static const float g_vertices[] = {
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,
};

static const float g_uvs[] = {
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f
};

static const unsigned int g_indices[] = {
	0, 1, 3,
	1, 2, 3
};

static const int g_tileWidth = 48;
static const int g_tileHeight = 48;

static const char* g_tileSheetOne = "Data/Maps/TileSheets/tileSheetOne.png";
static const int g_tileSheetWidth = 524;
static const int g_tileSheetHeight = 524;

static const char g_fileHeader[4] = { 'K', 'A', 'R', 'T' };

Map::Map(int width, int height, Shader* shader, DrawRectangleFn drawRectangleFn) :
	m_width ( width ),
	m_height ( height ),
	m_shader ( shader ),
	m_drawRectangleFn ( drawRectangleFn )
{
	glCreateVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glCreateBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glNamedBufferStorage(m_vertexBuffer, sizeof(float) * 8, g_vertices, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glCreateBuffers(1, &m_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvBuffer);
	glNamedBufferStorage(m_uvBuffer, sizeof(float) * 8, g_uvs, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glCreateBuffers(1, &m_indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
	glNamedBufferStorage(m_indicesBuffer, sizeof(unsigned int) * 6, g_indices, 0);

	m_tiles.resize(m_width * m_height);
	m_tiles[0] = 0;

	glCreateBuffers(1, &m_tileBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_tileBuffer);
	glNamedBufferStorage(m_tileBuffer, sizeof(GLushort) * m_tiles.size(), &m_tiles[0], GL_DYNAMIC_STORAGE_BIT);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_UNSIGNED_SHORT, GL_FALSE, 0, (void*)0);
	glVertexAttribDivisor(2, 1);

	m_tileSheet = SOIL_load_OGL_texture(g_tileSheetOne, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
	if (!m_tileSheet) {
		Log::get().write(L_ERROR, "Error loading tile sheet");
	}

	double pixelWidth = (1.0 / (double)g_tileSheetWidth);
	double pixelHeight = (1.0 / (double)g_tileSheetHeight);

	m_tileUvWidth = pixelWidth * g_tileWidth;
	m_tileUvHeight = pixelHeight * g_tileHeight;
	m_tileUvXOffset = pixelWidth * 4; // padding
	m_tileUvYOffset = pixelHeight * 4;
	Log::get().write(L_INFO, m_tileUvXOffset, " ", m_tileUvYOffset);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Map::~Map() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_uvBuffer);
	glDeleteBuffers(1, &m_indicesBuffer);
	glDeleteBuffers(1, &m_tileBuffer);
	glDeleteTextures(1, &m_tileSheet);
}

void Map::draw(bool p_drawLines) {
	glBindVertexArray(m_vao);
	m_shader->use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_tileSheet);

	m_shader->setBool("lines", false);
	m_shader->setInt("width", m_width);
	m_shader->setInt("height", m_height);
	m_shader->setInt("tileWidth", g_tileWidth);
	m_shader->setInt("tileHeight", g_tileHeight);
	m_shader->setDouble("uvWidth", m_tileUvWidth);
	m_shader->setDouble("uvHeight", m_tileUvHeight);
	m_shader->setDouble("uvXOffset", m_tileUvXOffset);
	m_shader->setDouble("uvYOffset", m_tileUvYOffset);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_width * m_height);

	if (p_drawLines) {
		m_shader->setBool("lines", true);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_width * m_height);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Map::drawMarker() {
		auto color = glm::vec4(.9, .7, .4, 0.6);
		m_drawRectangleFn(m_marker, color, 0);
}

void Map::setTile(double x, double y, unsigned int id) {
	x /= g_tileWidth;
	y /= g_tileHeight;

	if (x < 0 || y < 0) {
		return;
	}

	if (x >= m_width || y >= m_height) {
		return;
	}

	int index = (int)x + (int)y * m_width;

	if (m_tiles[index] != id) {
		m_tiles[index] = id;

		glBindBuffer(GL_ARRAY_BUFFER, m_tileBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLushort) * index, sizeof(GLushort), &m_tiles[index]);
	}
}

void Map::setMarker(double x, double y, int flag) {
	if (flag == MarkerFlag::CENTER) {
		x /= g_tileWidth;
		y /= g_tileHeight;

		x = floor(x) + 0.5;
		y = floor(y) + 0.5;

		x *= g_tileWidth;
		y *= g_tileHeight;

		m_marker = glm::vec4(x,	y, g_tileWidth, g_tileHeight);
	}
	else if (flag == MarkerFlag::CORNER) {
		x /= g_tileWidth;
		y /= g_tileHeight;

		float xFraction = x - (int)x;
		float yFraction = y - (int)y;

		if (xFraction < 0.5)	xFraction = 0.25;
		else					xFraction = 0.75;
		if (yFraction < 0.5)	yFraction = 0.25;
		else					yFraction = 0.75;

		x = (int)x + xFraction;
		y = (int)y + yFraction;

		x *= g_tileWidth;
		y *= g_tileHeight;

		m_marker = glm::vec4(x, y, 0.5f * g_tileWidth, 0.5f * g_tileHeight);
	}
}

glm::vec2 Map::center(double x, double y) {
	x /= g_tileWidth;
	y /= g_tileHeight;

	x = floor(x) + 0.5;
	y = floor(y) + 0.5;

	x *= g_tileWidth;
	y *= g_tileHeight;

	return glm::vec2(x, y);
}

glm::vec2 Map::corner(double x, double y) {
	x /= g_tileWidth;
	y /= g_tileHeight;

	float xFraction = x - (int)x;
	float yFraction = y - (int)y;

	if (xFraction < 0.5)	xFraction = 0.25;
	else					xFraction = 0.75;
	if (yFraction < 0.5)	yFraction = 0.25;
	else					yFraction = 0.75;

	x = (int)x + xFraction;
	y = (int)y + yFraction;

	x *= g_tileWidth;
	y *= g_tileHeight;

	return glm::vec2(x, y);
}

void Map::create(CreateNewMapDialog createNewMapDialog) {
	m_width = createNewMapDialog.width;
	m_height = createNewMapDialog.height;
	m_tiles.resize(m_width * m_height);
	std::fill(m_tiles.begin(), m_tiles.end(), createNewMapDialog.tile);
	m_name = createNewMapDialog.name;
	m_file = "";

	reloadTiles();
}

/*
* Structure of a Map File
* Magic num = KART  | 4B 41 52 54
*********************************
* type  | size in B | data      *
* ----------------------------- *
* int   | 4         | magic num *
* int   | 4         | width     *
* int   | 4         | height    *
* short | w * h * 2 | tiles     *
* uint32| 4         | CRC       *
* *******************************
*/

void Map::save(const char* p_file) {
	std::string fileName = std::string(p_file) + ".kart";
	Log::get().write(L_INFO, "Saving map at: ", fileName);

	if (fileName.size() == 0) {
		Log::get().write(L_ERROR, "Can't save empty file");
		return;
	}

	std::ofstream file(fileName, std::fstream::trunc | std::fstream::binary);
	if (file.is_open()) {
		uint32_t crc = calculateCRC(m_width, m_height, m_tiles);

		file.write(g_fileHeader, sizeof(g_fileHeader));
		file.write((char*)&m_width, sizeof(m_width));
		file.write((char*)&m_height, sizeof(m_height));
		file.write((char*)&m_tiles[0], sizeof(GLushort) * m_tiles.size());
		file.write((char*)&crc, sizeof(crc));

		m_file = p_file;
	} 
	else {
		char buf[50];
		strerror_s(buf, 50, errno);
		Log::get().write(L_ERROR, "I/O error saving map.\n", buf);
		return;
	}

	Log::get().write(L_INFO, "Map saved");
}

void Map::load(const char* p_file) {
	Log::get().write(L_INFO, "Loading map from: ", p_file);

	if (strlen(p_file) == 0) {
		Log::get().write(L_ERROR, "Can't load empty file");
		return;
	}

	int width;
	int height;
	std::vector<GLushort> tiles;

	std::ifstream file(p_file, std::ifstream::binary);

	if (file.is_open()) {
		try {
			char fileHeader[4];
			file.read(fileHeader, 4);

			for (int i = 0; i < 4; ++i) {
				if (fileHeader[i] != g_fileHeader[i]) {
					Log::get().write(L_ERROR, "Map file: is corrupt, invalid or missing file header");
					return;
				}
			}

			file.read((char*)&width, sizeof(width));
			file.read((char*)&height, sizeof(height));

			tiles.resize(width * height);
			file.read((char*)&tiles[0], sizeof(GLushort) * tiles.size());

			std::uint32_t validCRC;
			file.read((char*)&validCRC, sizeof(validCRC));

			if (validCRC != calculateCRC(width, height, tiles)) {
				Log::get().write(L_ERROR, "Map file is corrupt bad checksum");
				return;
			}
		}
		catch (std::exception e) {
			Log::get().write(L_ERROR, "Error reading map file.\n", e.what());
			return;
		}
	}
	else {
		char buf[50];
		strerror_s(buf, 50, errno);
		Log::get().write(L_ERROR, "I/O error loading map.\n", buf);
		return;
	}

	m_width = width;
	m_height = height;
	m_tiles = tiles;
	m_file = p_file;
	m_name = m_file.substr(m_file.find_last_of("\\") + 1);
	m_name = m_name.substr(0, m_name.find_last_of("."));

	reloadTiles();

	Log::get().write(L_INFO, "Map loaded");
}

uint32_t Map::calculateCRC(int p_width, int p_height, const std::vector<GLushort>& p_tiles) const {
	std::uint32_t emptyCrc = 0;
	std::uint32_t crc = 0;

	CRC::Table<uint32_t, 32> table(CRC::CRC_32());

	crc = CRC::Calculate(g_fileHeader, 4, table);
	crc = CRC::Calculate(&p_width, sizeof(p_width), table, crc);
	crc = CRC::Calculate(&p_height, sizeof(p_height), table, crc);
	crc = CRC::Calculate(&p_tiles[0], sizeof(GLushort) * p_tiles.size(), table, crc);
	crc = CRC::Calculate(&emptyCrc, sizeof(std::uint32_t), table, crc);

	return crc;
}

void Map::reloadTiles() {
	glBindVertexArray(m_vao);
	glDeleteBuffers(1, &m_tileBuffer);
	glCreateBuffers(1, &m_tileBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_tileBuffer);
	glNamedBufferStorage(m_tileBuffer, sizeof(GLushort) * m_tiles.size(), &m_tiles[0], GL_DYNAMIC_STORAGE_BIT);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_UNSIGNED_SHORT, GL_FALSE, 0, (void*)0);
	glVertexAttribDivisor(2, 1);
}

const std::string* Map::getMapName() const {
	return &m_name;
}

const std::string* Map::getMapFile() const {
	return &m_file;
}