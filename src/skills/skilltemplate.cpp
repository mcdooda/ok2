#include <flat.h>
#include "skilltemplate.h"

namespace game
{
namespace skills
{

SkillTemplate::SkillTemplate() :
	m_cooldown(0.f),
	m_triggerFunction(LUA_NOREF)
{
	
}

SkillTemplate::~SkillTemplate()
{
	
}

} // skills
} // game


