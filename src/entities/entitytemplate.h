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
		
		inline void setTexture(flat::video::Texture* texture) { m_texture = texture; }
		inline flat::video::Texture* getTexture() const { return m_texture; }
		
		inline void setSpeed(float speed) { m_speed = speed; }
		inline float getSpeed() const { return m_speed; }
		
	protected:
		flat::video::Texture* m_texture;
		float m_speed;
};

}
}

#endif // GAME_ENTITIES_ENTITYTEMPLATE_H



