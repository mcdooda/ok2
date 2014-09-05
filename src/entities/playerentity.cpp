#include "playerentity.h"

namespace game
{
namespace entities
{

PlayerEntity::PlayerEntity()
{

}

PlayerEntity::~PlayerEntity()
{

}

void PlayerEntity::update(Game* game, float elapsedTime)
{
	const flat::input::Keyboard* keyboard = game->input->keyboard;
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
	
	m_sprite->moveBy(direction * speed * elapsedTime);
	
	//static const float pi8 = M_PI / 8.f;
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
}

} // entities
} // game



