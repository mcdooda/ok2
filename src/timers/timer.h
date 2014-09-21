#ifndef GAME_TIMERS_TIMER_H
#define GAME_TIMERS_TIMER_H

namespace game
{
namespace timers
{

class Timer
{
	public:
		Timer();
		~Timer();
		
		inline void setBeginTime(float beginTime) { m_beginTime = beginTime; }
		inline float getBeginTime() const { return m_beginTime; }
		
		inline void setDuration(float duration) { m_duration = duration; }
		inline float getDuration() const { return m_duration; }
		
		inline void setUpdateFunctionRef(int updateFunctionRef) { m_updateFunctionRef = updateFunctionRef; }
		inline int getUpdateFunctionRef() const { return m_updateFunctionRef; }
		
		inline void setEndFunctionRef(int endFunctionRef) { m_endFunctionRef = endFunctionRef; }
		inline int getEndFunctionRef() const { return m_endFunctionRef; }
		
		void updateTime(float time);
		
		inline float getElapsedTime() const { return m_elapsedTime; }
		inline float getProgression() const { return m_elapsedTime / m_duration; }
		
		inline bool isFinished() const { return m_elapsedTime >= m_duration; }
		
		inline void stop() { m_stopped = true; }
		inline bool isStopped() const { return m_stopped; }
		
	private:
		int m_updateFunctionRef;
		int m_endFunctionRef;
		float m_beginTime;
		float m_elapsedTime;
		float m_duration;
		bool m_stopped;
};

} // lua
} // game

#endif // GAME_TIMERS_TIMER_H



