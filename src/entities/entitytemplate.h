#ifndef GAME_ENTITIES_ENTITYTEMPLATE_H
#define GAME_ENTITIES_ENTITYTEMPLATE_H

#include <flat.h>

namespace game
{
namespace entities
{

class EntityTemplate
{
	public:
		EntityTemplate();
		virtual ~EntityTemplate();
		
		inline void setName(const std::string& name) { m_name = name; }
		inline const std::string& getName() const { return m_name; }
		
		void setSprite(flat::util::Sprite* sprite);
		inline flat::util::Sprite* getSprite() const { return m_sprite; }
		
		inline void setSpeed(float speed) { m_speed = speed; }
		inline float getSpeed() const { return m_speed; }
		
		inline void setPopFunctionRef(int popFunctionRef) { m_popFunctionRef = popFunctionRef; }
		inline int getPopFunctionRef() const { return m_popFunctionRef; }
		
		inline void setUpdateFunctionRef(int updateFunctionRef) { m_updateFunctionRef = updateFunctionRef; }
		inline int getUpdateFunctionRef() const { return m_updateFunctionRef; }
		
		inline float getRadius() const { return m_radius; }
		
	protected:
		flat::util::Sprite* m_sprite;
		float m_radius;
		std::string m_name;
		float m_speed;
		int m_popFunctionRef;
		int m_updateFunctionRef;
};

} // entities
} // game

#endif // GAME_ENTITIES_ENTITYTEMPLATE_H



