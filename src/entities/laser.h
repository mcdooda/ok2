#ifndef GAME_ENTITIES_LASER_H
#define GAME_ENTITIES_LASER_H

#include "lasertemplate.h"

namespace game
{
namespace entities
{

class Laser
{
	public:
		Laser();
		~Laser();
		
		void setTemplate(LaserTemplate* laserTemplate);
		
		inline void setPosition(const flat::geometry::Vector2& position) { m_position = position; }
		inline const flat::geometry::Vector2& getPosition() const { return m_position; }
		
		inline void setDirection(float direction) { m_direction = direction; }
		inline float getDirection() const { return m_direction; }
		
		inline void setLength(float length) { m_length = length; }
		inline float getLength() const { return m_length; }
		
	private:
		LaserTemplate* m_template;
		flat::util::Sprite* m_sprite;
		flat::geometry::Vector2 m_position;
		float m_direction;
		float m_length;
};

} // entities
} // game

#endif // GAME_ENTITIES_LASER_H



