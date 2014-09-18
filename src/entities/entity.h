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
		enum Side
		{
			ALLY,
			ENEMY,
			NUM_SIDES
		};
		
	public:
		Entity();
		virtual ~Entity();
		
		inline void setPass(flat::video::Pass* pass) { m_pass = pass; }
		
		virtual void setTemplate(EntityTemplate* entityTemplate);
		
		// rotation
		void setRotationZ(float rotationZ);
		
		const flat::geometry::Vector3& getRotation() const;
		
		// position
		void setPosition(const flat::geometry::Vector2& position);
		void setPositionX(float x);
		void setPositionY(float y);
		
		const flat::geometry::Vector2& getPosition() const;
		
		// matrix
		const flat::geometry::Matrix4& getModelMatrix();
		
		// update & draw
		virtual void update(Game* game, float elapsedTime);
		void draw(const flat::util::RenderSettings& renderSettings, const flat::geometry::Matrix4& viewMatrix);
		
		// lua callbacks
		int getPopFunctionRef() const;
		int getUpdateFunctionRef() const;
		
		inline void setDataRef(int dataRef) { m_dataRef = dataRef; }
		inline int getDataRef() { return m_dataRef; }
		
	protected:
		flat::util::Sprite* m_sprite;
		flat::video::Pass* m_pass;
		EntityTemplate* m_template;
		int m_dataRef;
};

}
}

#endif // GAME_ENTITIES_ENTITY_H



