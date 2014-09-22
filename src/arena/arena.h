#ifndef GAME_ARENA_ARENA_H
#define GAME_ARENA_ARENA_H

#include "cell.h"

namespace game
{
namespace arena
{

class Arena
{
	public:
		Arena(const flat::geometry::Vector2& size, float cellSize);
		~Arena();
		
		void addShip(entities::Ship* ship);
		void removeShip(entities::Ship* ship);
		void moveShip(entities::Ship* ship);
		
		void addMissile(entities::Missile* missile);
		void removeMissile(entities::Missile* missile);
		void moveMissile(entities::Missile* missile);
		
		inline const flat::geometry::Rectangle& getBoundingBox() const { return m_boundingBox; }
		
		bool isEntityOutOfArena(entities::Entity* entity);
		
		inline const flat::geometry::Vector2& getSize() const { return m_size; }
		
		const std::set<entities::Ship*>& getShips() const { return m_ships; }
		const std::set<entities::Missile*>& getMissiles() const { return m_missiles; }
		
		float getMinX() const;
		float getMinY() const;
		float getMaxX() const;
		float getMaxY() const;
		
	private:
		Cell* getEntityPositionCell(entities::Entity* entity);
		
	private:
		flat::geometry::Vector2 m_size;
		Cell** m_cells;
		int m_numCellsX;
		int m_numCellsY;
		float m_cellSize;
		flat::geometry::Rectangle m_boundingBox;
		
		std::set<entities::Ship*> m_ships;
		std::set<entities::Missile*> m_missiles;
};

} // arena
} // game

#endif // GAME_ARENA_ARENA_H



