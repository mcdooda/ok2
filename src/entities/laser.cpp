#include "laser.h"

namespace game
{
namespace entities
{

Laser::Laser()
{
	
}

Laser::~Laser()
{
	
}

void Laser::setTemplate(LaserTemplate* laserTemplate)
{
	m_template = laserTemplate;
	m_sprite = m_template->getSprite()->lightCopy();
}

} // entities
} // game



