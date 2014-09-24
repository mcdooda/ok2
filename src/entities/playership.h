#ifndef GAME_ENTITIES_PLAYERSHIP_H
#define GAME_ENTITIES_PLAYERSHIP_H

#include "ship.h"

namespace game
{
namespace entities
{

class PlayerShip : public Ship
{
	public:
		PlayerShip();
		virtual ~PlayerShip();
		
		virtual void update(Game* game, float time, float elapsedTime, arena::Arena* arena);
		
		void setLevel(unsigned int level);
		
	protected:
		void fitInArena(arena::Arena* arena);
		
	protected:
		unsigned int m_level;
		unsigned int m_experience;
};

} // entities
} // game

#endif // GAME_ENTITIES_PLAYERSHIP_H



