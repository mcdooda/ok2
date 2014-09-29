#include "arena.h"

namespace game
{
namespace arena
{

Arena::Arena(const flat::geometry::Vector2& size, float cellSize) :
	m_size(size),
	m_cellSize(cellSize)
{
	m_numCellsX = ceil(size.getX() / cellSize);
	m_numCellsY = ceil(size.getY() / cellSize);
	
	m_cells = new Cell*[m_numCellsX];
	for (int x = 0; x < m_numCellsX; x++)
		m_cells[x] = new Cell[m_numCellsY];
		
	m_minX = -size.getX() / 2.f;
	m_minY = -size.getY() / 2.f;
	m_maxX =  size.getX() / 2.f;
	m_maxY =  size.getY() / 2.f;
}

Arena::~Arena()
{
	for (int x = 0; x < m_numCellsX; x++)
		delete m_cells[x];
		
	delete m_cells;
}

void Arena::addShip(entities::Ship* ship)
{
	Cell* cell = getEntityPositionCell(ship);
	cell->addShip(ship);
	m_ships[ship->getSide()].insert(ship);
}

void Arena::removeShip(entities::Ship* ship)
{
	Cell* cell = ship->getCell();
	cell->removeShip(ship);
	m_ships[ship->getSide()].erase(ship);
}

void Arena::moveShip(entities::Ship* ship)
{
	Cell* oldCell = ship->getCell();
	Cell* newCell = getEntityPositionCell(ship);
	if (newCell != oldCell)
	{
		oldCell->removeShip(ship);
		
		if (newCell != NULL)
			newCell->addShip(ship);
	}
}

void Arena::addMissile(entities::Missile* missile)
{
	Cell* cell = getEntityPositionCell(missile);
	cell->addMissile(missile);
	m_missiles[missile->getSide()].insert(missile);
}

void Arena::removeMissile(entities::Missile* missile)
{
	Cell* cell = missile->getCell();
	cell->removeMissile(missile);
	m_missiles[missile->getSide()].erase(missile);
}

void Arena::moveMissile(entities::Missile* missile)
{
	Cell* oldCell = missile->getCell();
	Cell* newCell = getEntityPositionCell(missile);
	if (newCell != oldCell)
	{
		oldCell->removeMissile(missile);
		
		if (newCell != NULL)
			newCell->addMissile(missile);
	}
}

void Arena::removeEntity(entities::Entity* entity)
{
	if (entity->isShip())
		removeShip((entities::Ship*) entity);
		
	else
		removeMissile((entities::Missile*) entity);
}

void Arena::moveEntity(entities::Entity* entity)
{
	if (entity->isShip())
		moveShip((entities::Ship*) entity);
		
	else
		moveMissile((entities::Missile*) entity);
}

bool Arena::isEntityInside(entities::Entity* entity)
{
	if (entity->getCell() == NULL)
		return true;
		
	const flat::geometry::Vector2& position = entity->getPosition();
	float radius = entity->getRadius();
	
	return position.getX() > getMinX() - radius && position.getX() < getMaxX() + radius
	    && position.getY() > getMinY() - radius && position.getY() < getMaxY() + radius;
}

std::set<entities::Missile*> Arena::getCollidingMissiles(entities::Ship* ship) const
{
	std::set<entities::Missile*> collidingMissiles;
	float radius = ship->getHitRadius();
	flat::geometry::Vector2 position = ship->getPosition();
	entities::Entity::Side shipSide = ship->getSide();
	assertValidSide(shipSide);
	
	static const float missileMaxRadius = 30.f;
	
	int minX = getCellX(position.getX() - radius - missileMaxRadius);
	int maxX = getCellX(position.getX() + radius + missileMaxRadius);
	int minY = getCellY(position.getY() - radius - missileMaxRadius);
	int maxY = getCellY(position.getY() + radius + missileMaxRadius);
	
	int j = 0;
	
	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			const Cell& cell = m_cells[x][y];
			j++;
			
			for (int i = entities::Entity::ALLY; i < entities::Entity::NUM_SIDES; i++)
			{
				entities::Entity::Side side = (entities::Entity::Side) i;
				
				if (side != shipSide)
				{
					const std::set<entities::Missile*>& cellMissiles = cell.getMissiles(side);
				
					for (std::set<entities::Missile*>::iterator it = cellMissiles.begin(); it != cellMissiles.end(); it++)
					{
						if (collides(ship, *it))
							collidingMissiles.insert(*it);
					}
				}
			}
		}
	}
	
	return collidingMissiles;
}

flat::geometry::Vector2 Arena::getPlayerPopPosition() const
{
	return flat::geometry::Vector2(0, m_minY * 3.f / 4.f);
}

Cell* Arena::getEntityPositionCell(entities::Entity* entity)
{
	const flat::geometry::Vector2& position = entity->getPosition();
	int x = getCellX(position.getX());
	int y = getCellY(position.getY());
	return &m_cells[x][y];
}

bool Arena::collides(entities::Entity* a, entities::Entity* b) const
{
	float collisionDistance = (a->getHitRadius() + b->getHitRadius()) / 2;
	return (a->getPosition() - b->getPosition()).distanceSquared() < collisionDistance * collisionDistance;
}

int Arena::getCellX(float x) const
{
	int cellX = (int) floor((x - m_minX) / m_cellSize);
	
	if (cellX < 0)
		cellX = 0;
		
	else if (cellX >= m_numCellsX)
		cellX = m_numCellsX - 1;
		
	return cellX;
}

int Arena::getCellY(float y) const
{
	int cellY = (int) floor((y - m_minY) / m_cellSize);
	
	if (cellY < 0)
		cellY = 0;
		
	else if (cellY >= m_numCellsY)
		cellY = m_numCellsY - 1;
		
	return cellY;
}

} // arena
} // game



