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

void EntityTemplate::setSprite(flat::util::Sprite* sprite)
{
	m_sprite = sprite;
	const flat::geometry::Vector2& textureSize = m_sprite->getTexture()->getSize();
	m_radius = (textureSize.getX() + textureSize.getY()) / 4.f;
}

} // entities
} // game



