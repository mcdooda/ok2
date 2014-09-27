#ifndef GAME_ENTITIES_MISSILETEMPLATE_H
#define GAME_ENTITIES_MISSILETEMPLATE_H

#include "entitytemplate.h"

namespace game
{
namespace entities
{

class MissileTemplate : public EntityTemplate
{
	public:
		MissileTemplate();
		virtual ~MissileTemplate();
		
		inline void setDamage(int damage) { m_damage = damage; }
		inline int getDamage() const { return m_damage; }
		
	protected:
		int m_damage;
};

} // entities
} // game

#endif // GAME_ENTITIES_MISSILETEMPLATE_H



