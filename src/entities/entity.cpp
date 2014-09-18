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

const flat::geometry::Vector3& Entity::getRotation() const
{
	return m_sprite->getRotation();
}

void Entity::setPosition(const flat::geometry::Vector2& position)
{
	m_sprite->setPosition(position);
}

void Entity::setPositionX(float x)
{
	m_sprite->setPositionX(x);
}

void Entity::setPositionY(float y)
{
	m_sprite->setPositionY(y);
}

const flat::geometry::Vector2& Entity::getPosition() const
{
	return m_sprite->getPosition();
}

const flat::geometry::Matrix4& Entity::getModelMatrix()
{
	return m_sprite->getModelMatrix();
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



