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
		direction.x = -1.f;
	
	else if (rightPressed && !leftPressed)
		direction.x = 1.f;
	
	if (upPressed && !downPressed)
		direction.y = 1.f;
	
	else if (downPressed && !upPressed)
		direction.y = -1.f;
		
	direction = direction.normalize();
	
	float speed = m_template->getSpeed();
	m_speed = direction * speed;
	
	m_sprite->moveBy(m_speed * elapsedTime);
	
	static const float pi6 = M_PI / 6.f;
	static const float epsilon = 0.001f;
	float slowRotationSpeed = speed / 150.f;
	float fastRotationSpeed = speed / 50.f;
	
	flat::geometry::Vector3 rotation = m_sprite->getRotation();
	
	if (direction.x == 0.f)
	{
		if (rotation.y > epsilon)
		{
			rotation.y = rotation.y - elapsedTime * slowRotationSpeed;
			if (rotation.y < 0.f)
				rotation.y = 0.f;
		}
		else if (rotation.y < -epsilon)
		{
			rotation.y = rotation.y + elapsedTime * slowRotationSpeed;
			if (rotation.y > 0.f)
				rotation.y = 0.f;
		}
	}
	else
	{
		rotation.y = rotation.y + elapsedTime * direction.x * fastRotationSpeed;
		
		if (rotation.y < -pi6)
			rotation.y = -pi6;
			
		else if (rotation.y > pi6)
			rotation.y = pi6;
	}
	
	if (direction.y == 0.f)
	{
		if (rotation.x > epsilon)
		{
			rotation.x = rotation.x - elapsedTime * slowRotationSpeed;
			
			if (rotation.x < 0.f)
				rotation.x = 0.f;
		}
		else if (rotation.x < -epsilon)
		{
			rotation.x = rotation.x + elapsedTime * slowRotationSpeed;
			if (rotation.x > 0.f)
				rotation.x = 0.f;
		}
	}
	else
	{
		rotation.x = rotation.x - elapsedTime * direction.y * fastRotationSpeed;
		
		if (rotation.x < -pi6)
			rotation.x = -pi6;
			
		else if (rotation.x > pi6)
			rotation.x = pi6;
	}
	
	m_sprite->setRotation(rotation);
	
	// trigger skills
	
	bool primaryFirePressed   = keyboard->isPressed(K(LCTRL)) || keyboard->isPressed(K(RCTRL));
	bool secondaryFirePressed = keyboard->isPressed(K(SPACE)) || keyboard->isPressed(K(SPACE));
	
	lua::triggerEntityUpdateFunction(game->luaState, this, time, elapsedTime);
	
	fitInArena(arena);
	
	if (primaryFirePressed)
	{
		if (m_primarySkill != nullptr && m_primarySkill->isReady(time))
			m_primarySkill->trigger(game, this, time);
	}
	
	fitInArena(arena);
	
	if (secondaryFirePressed)
	{
		if (m_secondarySkill != nullptr && m_secondarySkill->isReady(time))
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
	
	if (position.x < minX)
		position.x = minX;
		
	else if (position.x > maxX)
		position.x = maxX;
		
	if (position.y < minY)
		position.y = minY;
		
	else if (position.y > maxY)
		position.y = maxY;
		
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



