#include "entitytemplate.h"

namespace game
{
namespace entities
{

EntityTemplate::EntityTemplate() :
	m_popFunctionRef(LUA_NOREF),
	m_updateFunctionRef(LUA_NOREF)
{
	
}

EntityTemplate::~EntityTemplate()
{
	// TODO unref
}

} // entities
} // game



