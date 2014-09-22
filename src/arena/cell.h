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
		
	private:
		std::set<entities::Ship*> m_ships;
		std::set<entities::Missile*> m_missiles;
};

} // arena
} // game

#endif // GAME_ARENA_CELL_H



