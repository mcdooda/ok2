#include "skill.h"

namespace game
{
namespace skills
{

Skill::Skill(SkillTemplate* skillTemplate) :
	m_template(skillTemplate)
{
	// make it ready
	m_lastTriggered = -getCooldown();
}

Skill::~Skill()
{

}

bool Skill::isReady(float time)
{
	return time > m_lastTriggered + getCooldown();
}

float Skill::getRemainingCoolDownRatio(float time)
{
	float ratio = 1.f - (time - m_lastTriggered) / getCooldown();
	return ratio < 0.f ? 0.f : ratio;
}

void Skill::trigger(Game* game, entities::Ship* ship, float time)
{
	m_lastTriggered = time;
	
	int triggerFunction = m_template->getTriggerFunction();
	
	if (triggerFunction != LUA_NOREF)
	{
		lua_State* L = game->luaState;
		lua_pushinteger(L, triggerFunction);
		lua_gettable(L, LUA_REGISTRYINDEX);
		lua_pushlightuserdata(L, ship); // TODO full userdata object
		lua_call(L, 1, 0);
	}
}

float Skill::getCooldown()
{
	return m_template->getCooldown();
}

} // skills
} // game



