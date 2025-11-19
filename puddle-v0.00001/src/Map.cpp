#include "Map.h"

#include <GL/gl3w.h>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL/SOIL2.h>

#include "CRC.h"

#include "Program.h"

#include <iostream>
#include <fstream>

GLuint Map::m_vao = 0;
GLuint Map::m_vertexBuffer = 0;

static bool initialized = false;

static const char TILE_SHEET[] = "Data/Textures/tiles.bmp";
static int TILE_SHEET_WIDTH = 1600;
static int TILE_SHEET_HEIGHT = 1600;

static const char MAGIC_NUMBER[4] = { 'K', 'A', 'R', 'T' };
static const char DEFAULT_FILE[] = "Data/Maps/default.kart";

const static float vertices[] = {
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
};

Map::Map() :
	m_width	( 50 ),
	m_height ( 50 ),
    m_tileBuffer ( 0 ),
    m_tileSize ( glm::vec2(32, 32) ),
    m_file ( DEFAULT_FILE )
{
    m_tiles.resize(m_width * m_height);

    if (!initialized) {
        init();
    }
    else {
        glBindVertexArray(m_vao);
    }

    m_tileSheet = SOIL_load_OGL_texture(TILE_SHEET, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if (!m_tileSheet) {
        std::cout << "Error loading tile sheet\n";
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glCreateBuffers(1, &m_tileBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_tileBuffer);
    glNamedBufferStorage(m_tileBuffer, sizeof(GLushort) * m_tiles.size(), &m_tiles[0], GL_DYNAMIC_STORAGE_BIT);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_UNSIGNED_SHORT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(1, 1);
}

Map::~Map() {
    glDeleteTextures(1, &m_tileSheet);
    glDeleteBuffers(1, &m_tileBuffer);
    glDeleteBuffers(1, &m_vertexBuffer);
    glDeleteVertexArrays(1, &m_vao);
}

void Map::init() {
    glCreateVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glCreateBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glNamedBufferStorage(m_vertexBuffer, sizeof(float) * 2 * 6, &vertices[0], 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Map::draw(Program* program, int mode) {
    glBindVertexArray(m_vao);
    program->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_tileSheet);

    glm::mat4 model(1);
    glUniformMatrix4fv(program->location("model"), 1, GL_FALSE, &model[0][0]);

    glUniform2fv(program->location("tileSize"), 1, &m_tileSize[0]);
    glUniform1i(program->location("width"), m_width);
    glUniform1i(program->location("height"), m_height);
    glUniform1i(program->location("tileSheetWidth"), TILE_SHEET_WIDTH);
    glUniform1i(program->location("tileSheetHeight"), TILE_SHEET_HEIGHT);

    glDrawArraysInstanced(mode, 0, 6, (m_width * m_height));
}

void Map::setTile(double x, double y, GLushort tile) {
    x /= m_tileSize.x;
    y /= m_tileSize.y;

    int index = int(x) + int(y) * m_width;

    if (index < 0 || index > m_tiles.size()) {
        return;
    }

    if (m_tiles[index] != tile) {
        m_tiles[index] = tile;

        glBindBuffer(GL_ARRAY_BUFFER, m_tileBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLushort) * index, sizeof(GLushort), &m_tiles[index]);
    }
}

void Map::reloadTiles() {
    glBindBuffer(GL_ARRAY_BUFFER, m_tileBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLushort) * m_tiles.size(), &m_tiles[0]);
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

void Map::save(std::string_view path) {
    std::cout << "Saving at: " << path << "\n";
    std::ofstream file(path.data(), std::fstream::trunc | std::fstream::binary);
    if (file.is_open()) {
        auto crc = calculateCrc();

        file.write(MAGIC_NUMBER, 4);
        file.write((char*)&m_width, sizeof(m_width));
        file.write((char*)&m_height, sizeof(m_height));
        file.write((char*)&m_tiles[0], sizeof(GLushort) * m_tiles.size());
        file.write((char*)&crc, sizeof(crc));

        m_file = path;
    }
    else {
        char buf[50];
        strerror_s(buf, 50, errno);
        std::cout << "I/O Error saving map at: " << path << " | " << buf << "\n";
    }
}

void Map::load(std::string_view path) {
    std::cout << "Loading from: " << path << "\n";
    std::ifstream file(path.data(), std::ifstream::binary);

    if (file.is_open()) {
        try {
            char magicNumber[4];
            file.read(magicNumber, 4);

            for (int i = 0; i < 4; ++i) {
                if (magicNumber[i] != MAGIC_NUMBER[i]) {
                    std::cout << "Map File is corrupt, invlaid or no magic number. \n";
                }
            }

            file.read((char*)&m_width, sizeof(m_width));
            file.read((char*)&m_height, sizeof(m_height));

            if (m_width > 100000 || m_height > 100000) {
                // probably a corrupted file.
                m_width = 1000;
                m_height = 1000;
            }

            m_tiles.resize(m_width * m_height);
            file.read((char*)&m_tiles[0], sizeof(GLushort) * m_tiles.size());

            std::uint32_t validCrc;
            file.read((char*)&validCrc, sizeof(validCrc));

            if (validCrc != calculateCrc()) {
                std::cout << "Map file is corrupt\n";
            }

            m_file = path;

            reloadTiles();
        }
        catch (std::exception e) {
            std::cout << "Error reading map file: " << e.what() << "\n";
            system("PAUSE");
        }
    }
    else {
        char buf[50];
        strerror_s(buf, 50, errno);
        std::cout << "I/O Error loading map at: " << path << " | " << buf << "\n";
    }
}

uint32_t Map::calculateCrc() const {
    std::uint32_t emptyCrc;
    std::uint32_t crc;

    crc = CRC::Calculate(MAGIC_NUMBER, 4, CRC::CRC_32());
    crc = CRC::Calculate(&m_width, sizeof(m_width), CRC::CRC_32(), crc);
    crc = CRC::Calculate(&m_height, sizeof(m_height), CRC::CRC_32(), crc);
    crc = CRC::Calculate(&m_tiles[0], sizeof(GLushort) * m_tiles.size(), CRC::CRC_32(), crc);
    crc = CRC::Calculate(&emptyCrc, sizeof(std::uint32_t), CRC::CRC_32(), crc);

    return crc;
}