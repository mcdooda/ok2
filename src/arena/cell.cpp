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
	ship->setCell(this);
	assertValidSide(ship->getSide());
	m_ships[ship->getSide()].insert(ship);
}

void Cell::removeShip(entities::Ship* ship)
{
	ship->setCell(NULL);
	assertValidSide(ship->getSide());
	m_ships[ship->getSide()].erase(ship);
}

void Cell::addMissile(entities::Missile* missile)
{
	missile->setCell(this);
	assertValidSide(missile->getSide());
	m_missiles[missile->getSide()].insert(missile);
}

void Cell::removeMissile(entities::Missile* missile)
{
	missile->setCell(NULL);
	assertValidSide(missile->getSide());
	m_missiles[missile->getSide()].erase(missile);
}

} // arena
} // game



