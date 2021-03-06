#ifndef GAME_ARENA_ARENA_H
#define GAME_ARENA_ARENA_H

#include <map>
#include "cell.h"

namespace game
{
namespace entities
{
class Missile;
class PlayerShip;
}

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
		
		void removeEntity(entities::Entity* entity);
		void moveEntity(entities::Entity* entity);
		
		bool isEntityInside(entities::Entity* entity);
		
		inline const flat::geometry::Vector2& getSize() const { return m_size; }
		
		inline const std::set<entities::Ship*>& getShips(entities::Entity::Side side) const { return m_ships[side]; }
		inline const std::set<entities::Missile*>& getMissiles(entities::Entity::Side side) const { return m_missiles[side]; }
		inline int getNumShips(entities::Entity::Side side) const { return m_ships[side].size(); }
		inline int getNumMissiles(entities::Entity::Side side) const { return m_missiles[side].size(); }
		
		entities::Entity* getEntityById(int id) const;
		
		std::set<entities::Missile*> getCollidingMissiles(entities::Ship* ship) const;
		
		inline float getMinX() const { return m_minX; }
		inline float getMinY() const { return m_minY; }
		inline float getMaxX() const { return m_maxX; }
		inline float getMaxY() const { return m_maxY; }
		
		inline const flat::geometry::Vector2& getCenter() const { return m_center; }
		
		flat::geometry::Vector2 getPlayerPopPosition() const;
		
		entities::PlayerShip* getRandomPlayerShip(entities::Entity::Side side, flat::random::Random* random) const;
		
	private:
		Cell* getEntityPositionCell(entities::Entity* entity);
		
		bool collides(entities::Entity* a, entities::Entity* b) const;
		
		int getCellX(float x) const;
		int getCellY(float y) const;
		
		void setEntityId(entities::Entity* entity);
		void removeEntityId(entities::Entity* entity);
		
	private:
		flat::geometry::Vector2 m_size;
		Cell** m_cells;
		int m_numCellsX;
		int m_numCellsY;
		float m_cellSize;
		
		std::set<entities::Ship*> m_ships[entities::Entity::NUM_SIDES];
		std::set<entities::PlayerShip*> m_playerShips[entities::Entity::NUM_SIDES];
		std::set<entities::Missile*> m_missiles[entities::Entity::NUM_SIDES];
		
		std::map<int, entities::Entity*> m_entitiesById;
		
		flat::geometry::Vector2 m_center;
		float m_minX;
		float m_minY;
		float m_maxX;
		float m_maxY;
		
		int m_nextEntityId;
};

} // arena
} // game

#endif // GAME_ARENA_ARENA_H



