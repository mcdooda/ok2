#include "ship.h"
#include "shiptemplate.h"

namespace game
{
namespace entities
{

Ship::Ship() : Entity(),
	m_primarySkill(NULL),
	m_secondarySkill(NULL)
{
	
}

Ship::~Ship()
{
	delete m_primarySkill;
	delete m_secondarySkill;
}

void Ship::setTemplate(EntityTemplate* entityTemplate)
{
	Entity::setTemplate(entityTemplate);
	ShipTemplate* shipTemplate = (ShipTemplate*) m_template;
	m_health = shipTemplate->getHealth();
	setTemplateSkills();
}

void Ship::setTemplateSkills(unsigned int level)
{
	ShipTemplate* shipTemplate = (ShipTemplate*) m_template;
	setSkill(m_primarySkill,   shipTemplate->getPrimarySkillTemplate(1));
	setSkill(m_secondarySkill, shipTemplate->getSecondarySkillTemplate(1));
}

void Ship::setSkill(skills::Skill*& skill, skills::SkillTemplate* skillTemplate)
{
	if (skillTemplate != NULL)
		skill = new skills::Skill(skillTemplate);
		
	else
	{
		delete skill;
		skill = NULL;
	}
}

bool Ship::update(Game* game, float time, float elapsedTime, arena::Arena* arena)
{
	bool remove = Entity::update(game, time, elapsedTime, arena);
	
	if (m_primarySkill != NULL && m_primarySkill->isReady(time))
		m_primarySkill->trigger(game, this, time);
		
	if (m_secondarySkill != NULL && m_secondarySkill->isReady(time))
		m_secondarySkill->trigger(game, this, time);
		
	return remove;
}

void Ship::setPopTime(float popTime)
{
	Entity::setPopTime(popTime);
	
	if (m_primarySkill != NULL)
		m_primarySkill->setLastTriggeredTime(popTime);
		
	if (m_secondarySkill != NULL)
		m_secondarySkill->setLastTriggeredTime(popTime);
}

void Ship::dealDamage(Missile* missile, float time)
{
	m_health -= missile->getDamage();
}

int Ship::getMaxHealth() const
{
	return ((ShipTemplate*) m_template)->getHealth();
}

} // entities
} // game



