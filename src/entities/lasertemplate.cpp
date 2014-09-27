#include "lasertemplate.h"

namespace game
{
namespace entities
{

LaserTemplate::LaserTemplate() :
	m_popFunctionRef(LUA_NOREF),
	m_updateFunctionRef(LUA_NOREF)
{
	
}

LaserTemplate::~LaserTemplate()
{
	
}

} // entities
} // game



