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
}

void Cell::removeShip(entities::Ship* ship)
{
	m_ships.erase(ship);
}

void Cell::addMissile(entities::Missile* missile)
{
	m_missiles.insert(missile);
}

void Cell::removeMissile(entities::Missile* missile)
{
	m_missiles.erase(missile);
}

} // arena
} // game



