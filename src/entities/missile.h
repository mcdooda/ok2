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
};

} // entities
} // game

#endif // GAME_ENTITIES_MISSILE_H



