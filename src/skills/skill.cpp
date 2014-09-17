#include "skill.h"

namespace game
{
namespace skills
{

Skill::Skill()
{
	
}

Skill::~Skill()
{

}

bool Skill::isReady(float time)
{
	return time > m_lastTriggered + m_coolDown;
}

float Skill::getRemainingCoolDownRatio(float time)
{
	float ratio = 1.f - (time - m_lastTriggered) / m_coolDown;
	return ratio < 0.f ? 0.f : ratio;
}

void Skill::trigger(Game* game, float time)
{
	m_lastTriggered = time;
}

} // skills
} // game



