#ifndef TIMER_H
#define TIMER_H

class Timer {
public:
	Timer(__int64 durationMillis);
	~Timer();

	bool elapsed();

	void setDuration(__int64 duration);

	void setOffset(__int64 offset);

	__int64* getDurationPtr();

	__int64* getOffsetPtr();
private:
	__int64 m_time;
	__int64 m_durationMillis;
	__int64 m_offset;
};

#endif