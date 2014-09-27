#ifndef GAME_ENTITIES_LASERTEMPLATE_H
#define GAME_ENTITIES_LASERTEMPLATE_H

#include <flat.h>

namespace game
{
namespace entities
{

class LaserTemplate
{
	public:
		LaserTemplate();
		~LaserTemplate();
		
		inline void setSprite(flat::util::Sprite* sprite) { m_sprite = sprite; }
		inline flat::util::Sprite* getSprite() const { return m_sprite; }
		
		inline void setSpeed(float speed) { m_speed = speed; }
		inline float getSpeed() const { return m_speed; }
		
		inline void setAnimationSpeed(float animationSpeed) { m_animationSpeed = animationSpeed; }
		inline float getAnimationSpeed() const { return m_animationSpeed; }
		
		inline void setWidth(float width) { m_width = width; }
		inline float getWidth() const { return m_width; }
		
		inline void setPopFunctionRef(int popFunctionRef) { m_popFunctionRef = popFunctionRef; }
		inline int getPopFunctionRef() const { return m_popFunctionRef; }
		
		inline void setUpdateFunctionRef(int updateFunctionRef) { m_updateFunctionRef = updateFunctionRef; }
		inline int getUpdateFunctionRef() const { return m_updateFunctionRef; }
		
	private:
		flat::util::Sprite* m_sprite;
		float m_speed;
		float m_animationSpeed;
		float m_width;
		int m_popFunctionRef;
		int m_updateFunctionRef;
};

} // entities
} // game

#endif // GAME_ENTITIES_LASERTEMPLATE_H



