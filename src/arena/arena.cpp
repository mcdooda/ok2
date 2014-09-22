#include "arena.h"

namespace game
{
namespace arena
{

Arena::Arena(const flat::geometry::Vector2& size, float cellSize) :
	m_size(size),
	m_cellSize(cellSize),
	m_boundingBox(flat::geometry::Vector2() - size / 2, size)
{
	m_numCellsX = ceil(size.getX() / cellSize);
	m_numCellsY = ceil(size.getY() / cellSize);
	
	m_cells = new Cell*[m_numCellsX];
	for (int x = 0; x < m_numCellsX; x++)
		m_cells[x] = new Cell[m_numCellsY];
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
	m_ships.insert(ship);
}

void Arena::removeShip(entities::Ship* ship)
{
	Cell* cell = ship->getCell();
	cell->removeShip(ship);
	ship->setCell(NULL);
	m_ships.erase(ship);
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
			
		ship->setCell(newCell);
	}
}

void Arena::addMissile(entities::Missile* missile)
{
	Cell* cell = getEntityPositionCell(missile);
	cell->addMissile(missile);
	m_missiles.insert(missile);
}

void Arena::removeMissile(entities::Missile* missile)
{
	Cell* cell = missile->getCell();
	cell->removeMissile(missile);
	missile->setCell(NULL);
	m_missiles.erase(missile);
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
			
		missile->setCell(newCell);
	}
}

bool Arena::isEntityOutOfArena(entities::Entity* entity)
{
	if (entity->getCell() == NULL)
		return true;
		
	const flat::geometry::Vector2& position = entity->getPosition();
	float radius = entity->getRadius();
	
	return position.getX() > -radius && position.getX() < m_size.getX() + radius
	    && position.getY() > -radius && position.getY() < m_size.getY() + radius;
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

float Arena::getMinX() const
{
	return m_boundingBox.getPosition().getX();
}

float Arena::getMinY() const
{
	return m_boundingBox.getPosition().getY();
}

float Arena::getMaxX() const
{
	return m_boundingBox.getPosition().getX() + m_boundingBox.getSize().getX();
}

float Arena::getMaxY() const
{
	return m_boundingBox.getPosition().getY() + m_boundingBox.getSize().getY();
}

} // arena
} // game



