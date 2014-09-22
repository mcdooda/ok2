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
		
		void addEntity(entities::Entity* entity);
		void removeEntity(entities::Entity* entity);
		void moveEntity(entities::Entity* entity);
		
		inline const flat::geometry::Rectangle& getBoundingBox() const { return m_boundingBox; }
		
		bool isEntityOutOfArena(entities::Entity* entity);
		
		inline const flat::geometry::Vector2& getSize() const { return m_size; }
		
	private:
		Cell* getEntityPositionCell(entities::Entity* entity);
		
	private:
		flat::geometry::Vector2 m_size;
		Cell** m_cells;
		unsigned int m_numCellsX;
		unsigned int m_numCellsY;
		float m_cellSize;
		flat::geometry::Rectangle m_boundingBox;
};

} // arena
} // game

#endif // GAME_ARENA_ARENA_H



