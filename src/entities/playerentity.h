#ifndef GAME_ENTITIES_PLAYERENTITY_H
#define GAME_ENTITIES_PLAYERENTITY_H

#include "entity.h"

namespace game
{
namespace entities
{

class PlayerEntity : public Entity
{
	public:
		PlayerEntity();
		virtual ~PlayerEntity();
		
		virtual void update(Game* game, float elapsedTime);
};

} // entities
} // game

#endif // GAME_ENTITIES_PLAYERENTITY_H



