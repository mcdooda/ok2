#include "skill.h"
#include "../entities/lua/entity.h"

namespace game
{
namespace skills
{

Skill::Skill(SkillTemplate* skillTemplate) :
	m_template(skillTemplate)
{
	// make it ready
	m_lastTriggered = -m_template->getCooldown();
}

Skill::~Skill()
{
	// TODO unref m_dataRef
}

bool Skill::isReady(float time)
{
	return time > m_lastTriggered + m_template->getCooldown();
}

float Skill::getRemainingCoolDownRatio(float time)
{
	float ratio = 1.f - (time - m_lastTriggered) / m_template->getCooldown();
	return ratio < 0.f ? 0.f : ratio;
}

void Skill::trigger(Game* game, entities::Ship* ship, float time)
{
	m_lastTriggered = time;
	
	int triggerFunctionRef = m_template->getTriggerFunctionRef();
	
	if (triggerFunctionRef != LUA_NOREF)
	{
		lua_State* L = game->luaState;
		lua_pushinteger(L, triggerFunctionRef);
		lua_gettable(L, LUA_REGISTRYINDEX);
		entities::lua::pushEntity(L, ship);
		lua_call(L, 1, 0);
	}
}

} // skills
} // game



