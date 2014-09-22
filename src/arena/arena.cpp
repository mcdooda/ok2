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

bool Arena::isEntityInside(entities::Entity* entity)
{
	if (entity->getCell() == NULL)
		return true;
		
	const flat::geometry::Vector2& position = entity->getPosition();
	float radius = entity->getRadius();
	
	return position.getX() > getMinX() - radius && position.getX() < getMaxX() + radius
	    && position.getY() > getMinY() - radius && position.getY() < getMaxY() + radius;
}

Cell* Arena::getEntityPositionCell(entities::Entity* entity)
{
	const flat::geometry::Vector2& position = entity->getPosition();
	int x = (int) floor(position.getX() / m_cellSize);
	int y = (int) floor(position.getY() / m_cellSize);
	
	if (x < 0)
		x = 0;
	else if (x >= m_numCellsX)
		x = m_numCellsX - 1;
		
	if (y < 0)
		y = 0;
	else if (y >= m_numCellsY)
		y = m_numCellsY - 1;
	
	return &m_cells[x][y];
}

} // arena
} // game



