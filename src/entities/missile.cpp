#include "missile.h"
#include "missiletemplate.h"

namespace game
{
namespace entities
{

Missile::Missile() : Entity()
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



