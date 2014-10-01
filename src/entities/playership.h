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
		
		virtual bool update(Game* game, float time, float elapsedTime, arena::Arena* arena);
		
		void setLevel(unsigned int level);
		
		virtual float getHitRadius() const;
		
		virtual void dealDamage(Missile* missile, float time);
		
		virtual void die(arena::Arena* arena, float time);
		
		virtual void killedShip(Ship* ship);
		
	protected:
		void fitInArena(arena::Arena* arena);
		bool isInvincible(float time);
		
	protected:
		unsigned int m_numLives;
		float m_lastDeath;
		unsigned int m_level;
		unsigned int m_experience;
};

} // entities
} // game

#endif // GAME_ENTITIES_PLAYERSHIP_H



