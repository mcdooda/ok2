#include "arena.h"

namespace game
{
namespace arena
{

Arena::Arena(const flat::geometry::Vector2& size, float cellSize) :
	m_size(size),
	m_cellSize(cellSize),
	m_boundingBox(flat::geometry::Vector2(), size)
{
	m_numCellsX = ceil(size.getX() / cellSize);
	m_numCellsY = ceil(size.getY() / cellSize);
	
	m_cells = new Cell*[m_numCellsX];
	for (unsigned int x = 0; x < m_numCellsX; x++)
		m_cells[x] = new Cell[m_numCellsY];
}

Arena::~Arena()
{
	for (unsigned int x = 0; x < m_numCellsX; x++)
		delete m_cells[x];
		
	delete m_cells;
}

void Arena::addEntity(entities::Entity* entity)
{
	Cell* cell = getEntityPositionCell(entity);
	cell->addEntity(entity);
}

void Arena::removeEntity(entities::Entity* entity)
{
	Cell* cell = entity->getCell();
	cell->removeEntity(entity);
	entity->setCell(NULL);
}

void Arena::moveEntity(entities::Entity* entity)
{
	Cell* oldCell = entity->getCell();
	Cell* newCell = getEntityPositionCell(entity);
	if (newCell != oldCell)
	{
		oldCell->removeEntity(entity);
		
		if (newCell != NULL)
			newCell->addEntity(entity);
			
		entity->setCell(newCell);
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
	unsigned int x = (unsigned int) floor(position.getX() / m_cellSize);
	unsigned int y = (unsigned int) floor(position.getY() / m_cellSize);
	
	if (x >= 0 && x < m_numCellsX && y >= 0 && y < m_numCellsY)
		return &m_cells[x][y];
		
	else
		return NULL;
}

} // arena
} // game



