#include "missile.h"
#include "missiletemplate.h"

namespace game
{
namespace entities
{

Missile::Missile() : Entity(),
	m_shipId(0)
{
	
}

Missile::~Missile()
{
	
}

int Missile::getDamage() const
{
	return ((MissileTemplate*) m_template)->getDamage();
}

} // entities
} // game



