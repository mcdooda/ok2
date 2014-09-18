#include "ship.h"
#include "shiptemplate.h"

namespace game
{
namespace entities
{

Ship::Ship() :
	m_primarySkill(NULL),
	m_secondarySkill(NULL)
{
	
}

Ship::~Ship()
{
	
}

void Ship::setTemplate(EntityTemplate* entityTemplate)
{
	Entity::setTemplate(entityTemplate);
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

void Ship::update(Game* game, float elapsedTime)
{
	Entity::update(game, elapsedTime);
	
	float time = game->time->getTime();
	
	if (m_primarySkill != NULL && m_primarySkill->isReady(time))
		m_primarySkill->trigger(game, this, time);
		
	if (m_secondarySkill != NULL && m_secondarySkill->isReady(time))
		m_secondarySkill->trigger(game, this, time);
}

} // entities
} // game


