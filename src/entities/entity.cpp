#include "entity.h"

namespace game
{
namespace entities
{

Entity::Entity() :
	m_sprite(NULL)
{
	
}

Entity::~Entity()
{
	
}

void Entity::update(Game* game, float elapsedTime)
{
	m_sprite->moveBy(flat::geometry::Vector2(m_sprite->getRotation().getZ()) * m_template->getSpeed() * elapsedTime);
}

void Entity::draw(const flat::util::RenderSettings& renderSettings, const flat::geometry::Matrix4& viewMatrix)
{
	m_sprite->draw(renderSettings, viewMatrix);
}

} // entities
} // game



