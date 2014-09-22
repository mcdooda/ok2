#include "cell.h"

namespace game
{
namespace arena
{

Cell::Cell()
{
	
}

Cell::~Cell()
{
	
}

void Cell::addEntity(entities::Entity* entity)
{
	m_entities.insert(entity);
}

void Cell::removeEntity(entities::Entity* entity)
{
	m_entities.erase(entity);
}

} // arena
} // game



