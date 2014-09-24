#ifndef GAME_ARENA_CELL_H
#define GAME_ARENA_CELL_H

#include <set>
#include "../entities/ship.h"
#include "../entities/missile.h"

namespace game
{
namespace entities
{
	class Ship;
}

namespace arena
{

class Cell
{
	public:
		Cell();
		~Cell();
		
		void addShip(entities::Ship* ship);
		void removeShip(entities::Ship* ship);
		
		void addMissile(entities::Missile* missile);
		void removeMissile(entities::Missile* missile);
		
		const std::set<entities::Ship*>& getShips(entities::Entity::Side side) const { return m_ships[side]; }
		const std::set<entities::Missile*>& getMissiles(entities::Entity::Side side) const { return m_missiles[side]; }
		
	private:
		std::set<entities::Ship*> m_ships[entities::Entity::NUM_SIDES];
		std::set<entities::Missile*> m_missiles[entities::Entity::NUM_SIDES];
};

} // arena
} // game

#endif // GAME_ARENA_CELL_H



