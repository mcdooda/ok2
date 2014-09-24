#ifndef GAME_ENTITIES_ENTITY_H
#define GAME_ENTITIES_ENTITY_H

#include <flat.h>

#include "../game.h"
#include "entitytemplate.h"

namespace game
{
namespace arena
{
class Cell;
class Arena;
}

namespace entities
{

class Entity
{
	public:
		enum Side
		{
			ALLY,
			ENEMY,
			NUM_SIDES,
			NONE
		};
		
	public:
		Entity();
		virtual ~Entity();
		
		virtual void setTemplate(EntityTemplate* entityTemplate);
		
		// rotation
		virtual void setRotationZ(float rotationZ);
		
		const flat::geometry::Vector3& getRotation() const;
		
		// position
		void setPosition(const flat::geometry::Vector2& position);
		void setPositionX(float x);
		void setPositionY(float y);
		
		const flat::geometry::Vector2& getPosition() const;
		
		// matrix
		const flat::geometry::Matrix4& getModelMatrix();
		flat::geometry::Vector2 getAbsolutePosition(const flat::geometry::Vector2& relativePosition);
		
		// update & draw
		virtual void update(Game* game, float time, float elapsedTime, arena::Arena* arena);
		void draw(const flat::util::RenderSettings& renderSettings, const flat::geometry::Matrix4& viewMatrix);
		
		// lua callbacks
		int getPopFunctionRef() const;
		int getUpdateFunctionRef() const;
		
		inline void setDataRef(int dataRef) { m_dataRef = dataRef; }
		inline int getDataRef() { return m_dataRef; }
		
		inline const flat::geometry::Vector2& getSpeed() const { return m_speed; }
		
		virtual void setPopTime(float popTime);
		inline float getPopTime() const { return m_popTime; }
		
		inline void setCell(arena::Cell* cell) { m_cell = cell; }
		inline arena::Cell* getCell() const { return m_cell; }
		
		inline float getRadius() const { return m_template->getRadius(); }
		
		virtual bool isShip() const { return false; }
		virtual bool isMissile() const { return false; }
		
		inline Side getSide() const { return m_side; }
		inline void setSide(Side side) { m_side = side; }
		
	protected:
		flat::util::Sprite* m_sprite;
		EntityTemplate* m_template;
		int m_dataRef;
		flat::geometry::Vector2 m_speed;
		float m_popTime;
		arena::Cell* m_cell;
		bool m_enteredArena;
		Side m_side;
};

}
}

#endif // GAME_ENTITIES_ENTITY_H



