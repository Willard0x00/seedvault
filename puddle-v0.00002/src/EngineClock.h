#ifndef ENGINE_CLOCK_H
#define ENGINE_CLOCK_H

class EngineClock {
public:
	EngineClock();
	~EngineClock();

	static EngineClock& get();

	void startFrame();

	void endFrame();

	__int64 getCurrentTimeMs();

	__int64 getDeltaTimeMs() const;

	int getFramesPerSecond() const;

	const char* getTime();
private:
	static EngineClock* m_myClock;

	inline __int64 calcElapsedMs(__int64 startTimeMs, __int64 frequency, bool addToAverage = false);

	__int64 m_engineStartTimeMs;
	__int64 m_frameStartTimeMs;
	__int64 m_frequency;
	__int64 m_deltaTimeMs;

	char m_buffer[21];
	
	const static __int64 NUM_OF_FRAME_AVERAGES = 300;
	__int64 m_frameAverages[NUM_OF_FRAME_AVERAGES];
	__int64 m_frameAverageTotal;
	int m_frameAveragesIndex;

};

#endif