#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <iostream>
#include <mutex>

#include "EngineClock.h"

#define WRITE_STDOUT
#define WRITE_ALL_LOGS

#define L_WHITE "\x1b[38;2;255;255;255m"
#define L_RED "\x1b[38;2;255;204;204m"
#define L_ORANGE "\x1b[38;2;255;229;204m"
#define L_YELLOW "\x1b[38;2;255;255;204m"
#define L_GREEN "\x1b[38;2;204;255;229m"
#define L_BLUE "\x1b[38;2;204;255;255m"
#define L_VIOLET "\x1b[38;2;204;153;255m"
#define L_PINK "\x1b[38;2;255;204;255m"
#define L_GRAY "\x1b[38;2;192;192;192m"

#define L_strDEBUG "DEBUG"
#define L_strWARN "WARN"
#define L_strERROR "ERROR"
#define L_strINFO "INFO"
#define L_strSYSTEM "SYSTEM"

#define L_DEBUG 4
#define L_WARN 3
#define L_ERROR 1
#define L_INFO 2
#define L_SYSTEM 0

#define L_LOG_LEVEL 4

static std::mutex LOG_MUTEX;

class Log {
public:
	~Log();
	
	template<class... Args>
	void write(uint8_t level, Args ...args) {
#ifdef WRITE_ALL_LOGS
#ifdef WRITE_STDOUT
		if (level > L_LOG_LEVEL) {
			return;
		}

		std::lock_guard<std::mutex> guard(LOG_MUTEX);
		std::cout << "[" << EngineClock::get().getTime() << "] " << getLevelColor(level) << "[" << getLevelStr(level) << "] -> ";
		(std::cout << ... << args) << "\n";
		std::cout << L_GRAY;
#endif
		m_file << "[" << EngineClock::get().getTime() << "] [" << getLevelStr(level) << "] -> ";
		(m_file << ... << args) << "\n";
#endif
	}

	constexpr const char* getLevelStr(uint8_t level) const;
	constexpr const char* getLevelColor(uint8_t level) const;

	static Log& get();

	void shutdown();
private:
	Log(const char* file);

	static Log* m_myLog;

	std::fstream m_file;
};

#endif