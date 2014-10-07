#include "playership.h"
#include "lua/entity.h"

namespace game
{
namespace entities
{

PlayerShip::PlayerShip() : Ship(),
	m_numLives(2),
	m_lastDeath(-2.f),
	m_level(1),
	m_experience(0)
{

}

PlayerShip::~PlayerShip()
{

}

bool PlayerShip::update(Game* game, float time, float elapsedTime, arena::Arena* arena)
{
	const flat::input::Keyboard* keyboard = game->input->keyboard;
	
	// move ship
	
	bool leftPressed  = keyboard->isPressed(K(LEFT))  || keyboard->isPressed(K(A));
	bool rightPressed = keyboard->isPressed(K(RIGHT)) || keyboard->isPressed(K(D));
	bool upPressed    = keyboard->isPressed(K(UP))    || keyboard->isPressed(K(W));
	bool downPressed  = keyboard->isPressed(K(DOWN))  || keyboard->isPressed(K(S));
	
	flat::geometry::Vector2 direction;
	
	if (leftPressed && !rightPressed)
		direction.setX(-1.f);
	
	else if (rightPressed && !leftPressed)
		direction.setX(1.f);
	
	if (upPressed && !downPressed)
		direction.setY(1.f);
	
	else if (downPressed && !upPressed)
		direction.setY(-1.f);
		
	direction = direction.normalize();
	
	float speed = m_template->getSpeed();
	m_speed = direction * speed;
	
	m_sprite->moveBy(m_speed * elapsedTime);
	
	static const float pi6 = M_PI / 6.f;
	static const float epsilon = 0.001f;
	float slowRotationSpeed = speed / 150.f;
	float fastRotationSpeed = speed / 50.f;
	
	flat::geometry::Vector3 rotation = m_sprite->getRotation();
	
	if (direction.getX() == 0.f)
	{
		if (rotation.getY() > epsilon)
		{
			rotation.setY(rotation.getY() - elapsedTime * slowRotationSpeed);
			if (rotation.getY() < 0.f)
				rotation.setY(0.f);
		}
		else if (rotation.getY() < -epsilon)
		{
			rotation.setY(rotation.getY() + elapsedTime * slowRotationSpeed);
			if (rotation.getY() > 0.f)
				rotation.setY(0.f);
		}
	}
	else
	{
		rotation.setY(rotation.getY() + elapsedTime * direction.getX() * fastRotationSpeed);
		
		if (rotation.getY() < -pi6)
			rotation.setY(-pi6);
			
		else if (rotation.getY() > pi6)
			rotation.setY(pi6);
	}
	
	if (direction.getY() == 0.f)
	{
		if (rotation.getX() > epsilon)
		{
			rotation.setX(rotation.getX() - elapsedTime * slowRotationSpeed);
			
			if (rotation.getX() < 0.f)
				rotation.setX(0.f);
		}
		else if (rotation.getX() < -epsilon)
		{
			rotation.setX(rotation.getX() + elapsedTime * slowRotationSpeed);
			if (rotation.getX() > 0.f)
				rotation.setX(0.f);
		}
	}
	else
	{
		rotation.setX(rotation.getX() - elapsedTime * direction.getY() * fastRotationSpeed);
		
		if (rotation.getX() < -pi6)
			rotation.setX(-pi6);
			
		else if (rotation.getX() > pi6)
			rotation.setX(pi6);
	}
	
	m_sprite->setRotation(rotation);
	
	// trigger skills
	
	bool primaryFirePressed   = keyboard->isPressed(K(LCTRL)) || keyboard->isPressed(K(RCTRL));
	bool secondaryFirePressed = keyboard->isPressed(K(SPACE)) || keyboard->isPressed(K(SPACE));
	
	lua::triggerEntityUpdateFunction(game->luaState, this, time, elapsedTime);
	
	fitInArena(arena);
	
	if (primaryFirePressed)
	{
		if (m_primarySkill != NULL && m_primarySkill->isReady(time))
			m_primarySkill->trigger(game, this, time);
	}
	
	fitInArena(arena);
	
	if (secondaryFirePressed)
	{
		if (m_secondarySkill != NULL && m_secondarySkill->isReady(time))
			m_secondarySkill->trigger(game, this, time);
	}
	
	fitInArena(arena);
	
	if (isInvincible(time))
	{
		flat::video::Color color;
		color.setA((sin(time * 30.f) + 1.f) / 2.f);
		m_sprite->setColor(color);
	}
	else
		m_sprite->setColor(flat::video::Color::WHITE);
	
	return false;
}

void PlayerShip::setLevel(unsigned int level)
{
	if (level != m_level)
	{
		m_level = level;
		setTemplateSkills(level);
	}
}

float PlayerShip::getHitRadius() const
{
	return getRadius() * 0.7f;
}

void PlayerShip::fitInArena(arena::Arena* arena)
{
	flat::geometry::Vector2 position = getPosition();
	float radius = getRadius();
	int minX = arena->getMinX() + radius;
	int maxX = arena->getMaxX() - radius;
	int minY = arena->getMinY() + radius;
	int maxY = arena->getMaxY() - radius;
	
	if (position.getX() < minX)
		position.setX(minX);
		
	else if (position.getX() > maxX)
		position.setX(maxX);
		
	if (position.getY() < minY)
		position.setY(minY);
		
	else if (position.getY() > maxY)
		position.setY(maxY);
		
	setPosition(position);
}

void PlayerShip::dealDamage(Missile* missile, float time)
{
	if (!isInvincible(time))
		Ship::dealDamage(missile, time);
}

void PlayerShip::die(arena::Arena* arena, float time)
{
	m_numLives--;
	if (m_numLives > 0)
	{
		setPosition(arena->getPlayerPopPosition());
		m_health = getMaxHealth();
		m_lastDeath = time;
	}
	else
	{
		// GAME OVER
		arena->removeShip(this);
	}
}

bool PlayerShip::isInvincible(float time)
{
	return time - m_lastDeath < 2.f;
}

void PlayerShip::killedShip(Ship* ship)
{
	m_experience += ship->getExperienceValue();
	
	ShipTemplate* shipTemplate = (ShipTemplate*) m_template;
	unsigned int maxLevel = shipTemplate->getMaxLevel();
	
	while (m_level < maxLevel && m_experience > shipTemplate->getLevelExperience(m_level + 1))
		setLevel(m_level + 1);
}

} // entities
} // game



