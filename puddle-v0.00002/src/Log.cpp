#include "Log.h"

#include <iostream>
#include <filesystem>

#include "EngineClock.h"

Log* Log::m_myLog = nullptr;

static const char LOG_FILE[] = "log.txt";

Log::Log(const char* file)
{
	m_file.open(file, std::ios::out | std::ios::app);

	if (!m_file.is_open()) {
		std::cout << "Couldn't open a log at location: " << LOG_FILE << std::endl;
	} else {
		std::filesystem::path path(file);
		if (std::filesystem::file_size(path) > 50000000) {
			m_file.close();
			m_file.open(file, std::ios::out | std::ios::trunc);
		}
	}

}

Log::~Log() {
}

constexpr const char* Log::getLevelStr(uint8_t level) const {
	switch (level) {
	case L_SYSTEM:	return L_strSYSTEM;
	case L_ERROR:	return L_strERROR;
	case L_INFO:	return L_strINFO;
	case L_WARN:	return L_strWARN;
	case L_DEBUG:	return L_strDEBUG;
	default:		return "";
	}
}

constexpr const char* Log::getLevelColor(uint8_t level) const {
	switch (level) {
	case L_SYSTEM:	return L_PINK;
	case L_ERROR:	return L_RED;
	case L_INFO:	return L_BLUE;
	case L_WARN:	return L_ORANGE;
	case L_DEBUG:	return L_GREEN;
	default:		return L_GRAY;
	}
}


void Log::shutdown() {
	write(L_SYSTEM, "Shutting Down...");
	m_file << std::flush;
	std::cout << std::flush;
	m_file.close();

	delete m_myLog;
	m_myLog = nullptr;
}

Log& Log::get() {
	if (!m_myLog) {
		m_myLog = new Log(LOG_FILE);
	}
	return *m_myLog;
}