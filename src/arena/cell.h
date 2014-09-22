#ifndef GAME_ARENA_CELL_H
#define GAME_ARENA_CELL_H

#include <set>
#include "../entities/entity.h"

namespace game
{

namespace entities
{
class Entity;
}

namespace arena
{

class Cell
{
	public:
		Cell();
		~Cell();
		
		void addEntity(entities::Entity* entity);
		void removeEntity(entities::Entity* entity);
		
	private:
		std::set<entities::Entity*> m_entities;
};

} // arena
} // game

#endif // GAME_ARENA_CELL_H



