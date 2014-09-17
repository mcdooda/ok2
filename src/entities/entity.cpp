#include <iostream>
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

void Entity::setTemplate(EntityTemplate* entityTemplate)
{
	m_template = entityTemplate;
	m_sprite = m_template->getSprite()->lightCopy();
}

void Entity::setRotationZ(float rotationZ)
{
	m_sprite->setRotationZ(rotationZ);
}

void Entity::setPosition(const flat::geometry::Vector2& position)
{
	m_sprite->setPosition(position);
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



