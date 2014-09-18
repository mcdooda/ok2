#include <flat.h>
#include "skilltemplate.h"

namespace game
{
namespace skills
{

SkillTemplate::SkillTemplate() :
	m_cooldown(0.f),
	m_triggerFunctionRef(LUA_NOREF)
{
	
}

SkillTemplate::~SkillTemplate()
{
	// TODO unref m_triggerFunctionRef
}

} // skills
} // game


