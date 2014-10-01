#ifndef GAME_ENTITIES_MISSILE_H
#define GAME_ENTITIES_MISSILE_H

#include "entity.h"

namespace game
{
namespace entities
{
class Entity;

class Missile : public Entity
{
	public:
		Missile();
		virtual ~Missile();
		
		virtual bool isMissile() const { return true; }
		
		int getDamage() const;
		
		inline void setShipId(int shipId) { m_shipId = shipId; }
		inline int getShipId() const { return m_shipId; }
		
	private:
		int m_shipId;
};

} // entities
} // game

#endif // GAME_ENTITIES_MISSILE_H



