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

void Cell::addShip(entities::Ship* ship)
{
	m_ships.insert(ship);
	ship->setCell(this);
}

void Cell::removeShip(entities::Ship* ship)
{
	m_ships.erase(ship);
	ship->setCell(NULL);
}

void Cell::addMissile(entities::Missile* missile)
{
	m_missiles.insert(missile);
	missile->setCell(this);
}

void Cell::removeMissile(entities::Missile* missile)
{
	m_missiles.erase(missile);
	missile->setCell(NULL);
}

} // arena
} // game



