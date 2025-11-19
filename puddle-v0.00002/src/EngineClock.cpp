#include "EngineClock.h"

#include <Windows.h>
#include <stdio.h>

EngineClock* EngineClock::m_myClock = nullptr;

EngineClock::EngineClock() :
	m_engineStartTimeMs ( 0 ),
	m_frameStartTimeMs ( 0 ),
	m_frequency ( 0 ),
	m_deltaTimeMs ( 0 ),
	m_frameAveragesIndex ( 0 ),
	m_frameAverageTotal ( 0 )
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_engineStartTimeMs);

	memset(&m_frameAverages[0], 0, sizeof(__int64) * NUM_OF_FRAME_AVERAGES);
}

EngineClock::~EngineClock() {
	delete m_myClock;
	m_myClock = nullptr;
}

EngineClock& EngineClock::get() {
	if (!m_myClock) {
		m_myClock = new EngineClock();
	}
	return *m_myClock;
}

inline __int64 EngineClock::calcElapsedMs(__int64 startTime, __int64 frequency, bool addToAverage) {
	LARGE_INTEGER elapsedMs;
	LARGE_INTEGER currentTime;

	QueryPerformanceCounter(&currentTime);
	elapsedMs.QuadPart = currentTime.QuadPart - ((LARGE_INTEGER*)&startTime)->QuadPart;

	if (addToAverage) {
		m_frameAverageTotal -= m_frameAverages[m_frameAveragesIndex];
		m_frameAverages[m_frameAveragesIndex] = frequency / elapsedMs.QuadPart;
		m_frameAverageTotal += m_frameAverages[m_frameAveragesIndex];
		++m_frameAveragesIndex;

		if (m_frameAveragesIndex > NUM_OF_FRAME_AVERAGES - 1) {
			m_frameAveragesIndex = 0;
		}
	}

	elapsedMs.QuadPart *= 1000000;
	elapsedMs.QuadPart /= ((LARGE_INTEGER*)&frequency)->QuadPart;

	return (__int64)elapsedMs.QuadPart;
}

__int64 EngineClock::getCurrentTimeMs() {
	return calcElapsedMs(m_engineStartTimeMs, m_frequency);
}

void EngineClock::startFrame() {
	QueryPerformanceCounter((LARGE_INTEGER*)&m_frameStartTimeMs);
}

void EngineClock::endFrame() {
	m_deltaTimeMs = calcElapsedMs(m_frameStartTimeMs, m_frequency, true);
}

__int64 EngineClock::getDeltaTimeMs() const {
	return m_deltaTimeMs;
}

const char* EngineClock::getTime() {
	__int64 time = getCurrentTimeMs();

	int microSeconds = time % 1000;
	int milliSeconds = (time / 1000) % 1000;
	int seconds = (time / 1000000) % 60;
	int minutes = ((time / 1000000) / 60) % 60;
	int hours = (((time / 1000000) / 60)) / 60 % 24;
	int days = ((((time / 1000000) / 60) / 60) / 24);

	sprintf_s(m_buffer, "%03u:%02u:%02u:%02u:%03u:%03u", days, hours, minutes, seconds, milliSeconds, microSeconds);

	return m_buffer;
}

int EngineClock::getFramesPerSecond() const {
	return int(m_frameAverageTotal / NUM_OF_FRAME_AVERAGES);
}