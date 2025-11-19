#include "Sprite.h"

#include "Log.h"

#include <rapidjson/istreamwrapper.h>
#include <fstream>

#include <fstream>

#include <SOIL/SOIL2.h>

#include "Animation.h"

void print_h(int n) {
	printf("%x %x %x %x\n", n & 0xff, n >> 8 & 0xff, n >> 16 & 0xff, n >> 24 & 0xff);
}

Sprite::Sprite(const char* path) :
	m_id ( -1 ),
	m_texture ( -1 )
{
	Log::get().write(L_INFO, "Loading sprite file -> ", path);

	std::ifstream fileStream(path);
	rapidjson::IStreamWrapper iStreamWrapper(fileStream);

	rapidjson::Document document;
	document.ParseStream(iStreamWrapper);

	if (document.HasParseError()) {
		Log::get().write(L_ERROR, document.GetParseError());
		return;
	}

	if (!document.HasMember("Sprite")) {
		Log::get().write(L_ERROR, "Sprite file: ", path, " has no member 'Sprite'");
		return;
	}

	m_id = document["Sprite"]["id"].GetInt();
	std::string image = document["Sprite"]["image"].GetString();
	m_texture = SOIL_load_OGL_texture(image.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);

	if (m_texture == 0) {
		Log::get().write(L_ERROR, "Error loading image: ", image);
		return;
	}

	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &m_imgWidth);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &m_imgHeight);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for (auto it = document["Sprite"].MemberBegin(); it != document["Sprite"].MemberEnd(); ++it) {
		std::string v = it->name.GetString();

		if (strcmp(it->name.GetString(), "Animation") == 0) {
			Animation newAnimation;
			std::string name = it->value["name"].GetString();
			
			if (it->value.HasMember("stop")) {
				newAnimation.m_stop = it->value["stop"].GetBool();
			}

			for (auto itFrame = it->value.MemberBegin(); itFrame != it->value.MemberEnd(); ++itFrame) {
				if (strcmp(itFrame->name.GetString(), "name") == 0 || strcmp(itFrame->name.GetString(), "stop") == 0) {
					continue;
				}

				Frame newFrame;

				newFrame.m_frame = itFrame->value["frame"].GetInt();
				if (itFrame->value.HasMember("duration")) {
					newFrame.m_duration = itFrame->value["duration"].GetInt64();
					newAnimation.m_totalDuration += newFrame.m_duration;
					newFrame.m_durationSum = newAnimation.m_totalDuration;
				}

				if (itFrame->value.HasMember("position")) {
					newFrame.m_position.x = itFrame->value["position"].GetArray()[0].GetFloat();
					newFrame.m_position.y = itFrame->value["position"].GetArray()[1].GetFloat();
					newFrame.m_position.z = itFrame->value["position"].GetArray()[2].GetFloat();
				}

				if (itFrame->value.HasMember("scale")) {
					newFrame.m_scale.x = itFrame->value["scale"].GetArray()[0].GetFloat();
					newFrame.m_scale.y = itFrame->value["scale"].GetArray()[1].GetFloat();
				}

				if (itFrame->value.HasMember("rotation")) {
					newFrame.m_rotation = itFrame->value["rotation"].GetFloat();
				}

				newAnimation.m_frames.push_back(newFrame);
			}

			newAnimation.m_type = g_aniNameToKey(name);
			m_animations.emplace(newAnimation.m_type, newAnimation);
		}

	}

	m_spriteWidth = document["Sprite"]["spriteWidth"].GetUint();
	m_spriteHeight = document["Sprite"]["spriteHeight"].GetUint();
	m_spriteSize = m_spriteWidth * m_spriteHeight;

	double pixelWidth = (1.0 / (double)m_imgWidth);
	double pixelHeight = (1.0 / (double)m_imgHeight);

	m_spriteUvWidth = pixelWidth * m_spriteWidth;
	m_spriteUvHeight = pixelHeight * m_spriteHeight;
	m_spriteUvXOffset = pixelWidth + pixelWidth;
	m_spriteUvYOffset = pixelHeight + pixelHeight;

	m_frames = document["Sprite"]["frames"].GetUint();

	generateAlphaMasks();
}

Sprite::~Sprite() {
	for (auto& mask : m_alphaMasks) {
		delete[] mask;
	}
}

uint16_t Sprite::getId() const {
	return m_id;
}

GLuint Sprite::getTexture() const {
	return m_texture;
}

Animation* const Sprite::getAnimation(uint8_t key) {
	if (m_animations.find(key) != m_animations.end()) {
		return &m_animations[key];
	}
	return nullptr;
}

uint16_t Sprite::getSpriteWidth() const {
	return m_spriteWidth;
}

uint16_t Sprite::getSpriteHeight() const {
	return m_spriteHeight;
}

uint16_t Sprite::getImgWidth() const {
	return m_imgWidth;
}

uint16_t Sprite::getImgHeight() const {
	return m_imgHeight;
}

double Sprite::getSpriteUvWidth() const {
	return m_spriteUvWidth;
}

double Sprite::getSpriteUvHeight() const {
	return m_spriteUvHeight;
}

double Sprite::getSpriteUvXOffset() const {
	return m_spriteUvXOffset;
}

double Sprite::getSpriteUvYOffset() const {
	return m_spriteUvYOffset;
}

int Sprite::getSpriteSize() const {
	return m_spriteSize;
}

void Sprite::generateAlphaMasks() {
	m_alphaMasks.resize(m_frames);
	for (auto& mask : m_alphaMasks) {
		mask = new uint8_t[m_spriteWidth * m_spriteHeight];
	}

	unsigned int* img = new unsigned int[m_imgWidth * m_imgHeight];

	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, img);

	/*
	for (int i = 0; i < m_imgWidth * m_imgHeight; ++i) {
		print_h(img[i]);
	}
	*/

	auto skipXScanLine = [this](unsigned int& pixel) {
		pixel += m_imgWidth * 2;
	};

	auto skipYScanLine = [](unsigned int& pixel) {
		pixel += 2;
	};

	unsigned int pixel = 0;
	unsigned int pixelRow = 0;
	unsigned int spriteRow = 0;
	unsigned int spriteSize = m_spriteWidth * m_spriteHeight;
	unsigned int imgSize = m_imgWidth * m_imgHeight;
	unsigned int maskPixel = 0;
	unsigned int maskRow = 0;
	unsigned int xFrames = (m_imgWidth - 2) / (m_spriteWidth + 2);
	
	skipXScanLine(pixel);
	while (pixel < imgSize) {
		unsigned int frame = spriteRow * xFrames;
		unsigned int startingMaskPixel = maskPixel;
		skipYScanLine(pixel);

		while (pixel % m_imgWidth != 0) {
			//std::cout << (img[pixel] & 0xff) << " ";
			if (frame >= m_alphaMasks.size() || maskPixel >= spriteSize || pixel >= imgSize) {
				Log::get().write(L_ERROR, "Failed to generate alpha mask. sprite values width / height / frames / padding do not match with the image.");
				delete[] img;
				return;
			}

			m_alphaMasks[frame][maskPixel] = img[pixel] & 0xff;

			++pixel;
			++maskPixel;

			if (maskPixel % m_spriteWidth == 0) {
				++frame;
				skipYScanLine(pixel);
				maskPixel = startingMaskPixel;
			}
		}

		++pixelRow;
		maskPixel += m_spriteWidth;

		if (maskPixel == m_spriteSize) {
			skipXScanLine(pixel);
			++spriteRow;
		}
	}

	/*
	
	printf("\n");

	for (int y = 0; y < m_spriteHeight; ++y) {
		for (int x = 0; x < m_spriteWidth; ++x) {
			std::cout << int(m_alphaMasks[0][x + y * m_spriteWidth]) << " ";
		}
		printf("\n");
	}
	printf("\n");
	
	*/

	delete[] img;
}

const uint8_t* Sprite::getAlphaMask(int frame) const {
	if (frame >= 0 && frame < m_alphaMasks.size()) {
		return m_alphaMasks[frame];
	}
	return nullptr;
}