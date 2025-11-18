#include "file.h"

void File::read() {
	_data.clear();
	std::ifstream file(_filepath);
	std::string temp;
	size_t find = 0;

	while (std::getline(file, temp)) {
		find = temp.find('-');
		temp.erase(0, find + 2);
		_data.push_back(temp);
	}

	file.close();
}

void File::read(std::string path) {
	_data.clear();
	_setPath(path);
	std::ifstream file(path);
	std::string temp;
	size_t find = 0;

	while (std::getline(file, temp)) {
		find = temp.find('-');
		temp.erase(0, find + 2);
		_data.push_back(temp);
	}

	file.close();
}

void File::uread() {
	_udata.clear();
	std::ifstream file(_filepath, std::ios::binary);
	std::string line;

	while (std::getline(file, line)) {
		// find '-'
		size_t pos = line.find('-');
		if (pos == std::string::npos)
			continue;

		// skip "- "
		std::string trimmed = line.substr(pos + 2);

		// store as UTF-8 (string → u8string is safe)
		u8string utext(reinterpret_cast<const char8_t*>(trimmed.data()),
			reinterpret_cast<const char8_t*>(trimmed.data() + trimmed.size()));

		_udata.push_back(utext);
	}
}

void File::uread(std::string path) {
	_udata.clear();
	std::ifstream file(_filepath, std::ios::binary);
	std::string line;

	while (std::getline(file, line)) {
		// find '-'
		size_t pos = line.find('-');
		if (pos == std::string::npos)
			continue;

		// skip "- "
		std::string trimmed = line.substr(pos + 2);

		// store as UTF-8 (string → u8string is safe)
		u8string utext(reinterpret_cast<const char8_t*>(trimmed.data()),
			reinterpret_cast<const char8_t*>(trimmed.data() + trimmed.size()));

		_udata.push_back(utext);
	}
}


int File::getInt(int line) {
	line -= 1;
	if (line < int(_data.size()) && line >= 0) {
		if (_data[line] != "") {
			return std::stoi(_data[line]);
		}
	}
	std::cout << "line: " << line << " doesn't exist in " << _filepath << std::endl;
	return 0;
}

float File::getFloat(int line) {
	line -= 1;
	if (line < int(_data.size()) && line >= 0) {
		return std::stof(_data[line]);
	}
	std::cout << "line: " << line << " doesn't exist in " << _filepath << std::endl;
	return 0;
}

std::string File::getStr(int line) {
	line -= 1;
	if (line < int(_data.size()) && line >= 0) {
		return _data[line];
	}
	std::cout << "line: " << line << " doesn't exist in " << _filepath << std::endl;
	return "";
}

u8string File::getU16(int line) {
	line -= 1;
	if (line < int(_udata.size()) && line >= 0) {
		return _udata[line];
	}
	std::cout << "line: " << line << " doesn't exist in " << _filepath << std::endl;
	return { 0x00 };
}

bool File::exists(std::string path) {
	std::ifstream file(path);
	if (!file) {
		return false;
	}
	return true;
}

int File::getSize() {
	return _data.size();
}

void File::_setPath(const int& filenum) {
	switch (filenum) {
	case OPTIONS_FILE:
		_filepath = "Data/options.txt";
		break;
	case PLAYER_FILE:
		_filepath = "Data/player.txt";
		break;
	}
}

void File::_setPath(std::string filepath) {
	_filepath = filepath;
}