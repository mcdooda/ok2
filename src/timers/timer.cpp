#include "timer.h"
#include "lua/timer.h"

namespace game
{
namespace timers
{

Timer::Timer() :
	m_updateFunctionRef(LUA_NOREF),
	m_endFunctionRef(LUA_NOREF),
	m_elapsedTime(0),
	m_stopped(false)
{
	
}

Timer::~Timer()
{
	// TODO unref
}

void Timer::updateTime(float time)
{
	float elapsedTime = time - m_beginTime;
	m_elapsedTime = elapsedTime > m_duration ? m_duration : elapsedTime;
}

} // lua
} // game



