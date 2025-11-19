#include "Timer.h"

#include "EngineClock.h"

Timer::Timer(__int64 durationMillis) :
	m_time ( EngineClock::get().getCurrentTimeMs() / 1000 ),
	m_durationMillis ( durationMillis ),
	m_offset ( 0 )
{}

Timer::~Timer() {
}

bool Timer::elapsed() {
	__int64 currentTimeMs = EngineClock::get().getCurrentTimeMs() / 1000;

	if ((currentTimeMs + m_offset) - m_time > m_durationMillis) {
		m_time = currentTimeMs;
		return true;
	}

	return false;
}

void Timer::setDuration(__int64 duration) {
	m_durationMillis = duration;
}

void Timer::setOffset(__int64 offset) {
	m_offset = offset;
}

__int64* Timer::getDurationPtr() {
	return &m_durationMillis;
}

__int64* Timer::getOffsetPtr() {
	return &m_offset;
}
