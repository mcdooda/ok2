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
		~PlayerShip() override;
		
		bool update(Game* game, float time, float elapsedTime, arena::Arena* arena) override;
		
		void setLevel(unsigned int level);
		
		float getHitRadius() const override;
		
		void dealDamage(Missile* missile, float time) override;
		
		void die(arena::Arena* arena, float time) override;
		
		void killedShip(Ship* ship) override;
		
		bool isPlayerShip() const override { return true; }

		inline unsigned int getNumLives() const { return m_numLives; }
		
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



