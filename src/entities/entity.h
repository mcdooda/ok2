#ifndef GAME_ENTITIES_ENTITY_H
#define GAME_ENTITIES_ENTITY_H

#include <flat.h>

#include "../game.h"
#include "entitytemplate.h"

namespace game
{
namespace entities
{

class Entity
{
	public:
		Entity();
		virtual ~Entity();
		
		inline void setSprite(flat::util::Sprite* sprite) { m_sprite = sprite; }
		inline void setTemplate(EntityTemplate* template_) { m_template = template_; }
		
		inline void setRotationZ(float rotationZ) { m_sprite->setRotationZ(rotationZ); }
		
		virtual void update(Game* game, float elapsedTime);
		void draw(const flat::util::RenderSettings& renderSettings);
		
	protected:
		flat::util::Sprite* m_sprite;
		EntityTemplate* m_template;
};

}
}

#endif // GAME_ENTITIES_ENTITY_H



