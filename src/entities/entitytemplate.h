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
		
		inline void setSprite(flat::util::Sprite* sprite) { m_sprite = sprite; }
		inline flat::util::Sprite* getSprite() const { return m_sprite; }
		
		inline void setSpeed(float speed) { m_speed = speed; }
		inline float getSpeed() const { return m_speed; }
		
	protected:
		flat::util::Sprite* m_sprite;
		std::string m_name;
		float m_speed;
};

}
}

#endif // GAME_ENTITIES_ENTITYTEMPLATE_H



