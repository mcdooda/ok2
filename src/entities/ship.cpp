#include "ship.h"
#include "shiptemplate.h"

namespace game
{
namespace entities
{

Ship::Ship() : Entity(),
	m_primarySkill(nullptr),
	m_secondarySkill(nullptr)
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
	setSkill(m_primarySkill,   shipTemplate->getPrimarySkillTemplate(level));
	setSkill(m_secondarySkill, shipTemplate->getSecondarySkillTemplate(level));
}

void Ship::setSkill(skills::Skill*& skill, skills::SkillTemplate* skillTemplate)
{
	if (skillTemplate != nullptr)
		skill = new skills::Skill(skillTemplate);
		
	else
	{
		delete skill;
		skill = nullptr;
	}
}

bool Ship::update(Game* game, float time, float elapsedTime, arena::Arena* arena)
{
	bool remove = Entity::update(game, time, elapsedTime, arena);
	
	if (m_primarySkill != nullptr && m_primarySkill->isReady(time))
		m_primarySkill->trigger(game, this, time);
		
	if (m_secondarySkill != nullptr && m_secondarySkill->isReady(time))
		m_secondarySkill->trigger(game, this, time);
		
	static const float blinkDuration = 0.07f;
	if (m_lastHit > time - blinkDuration)
	{
		GLfloat gray = (m_lastHit - time) / blinkDuration;
		m_sprite->setColor(flat::video::Color(gray));
	}
	else
		m_sprite->setColor(flat::video::Color::WHITE);
		
	return remove;
}

void Ship::setPopTime(float popTime)
{
	Entity::setPopTime(popTime);
	
	if (m_primarySkill != nullptr)
		m_primarySkill->setLastTriggeredTime(popTime);
		
	if (m_secondarySkill != nullptr)
		m_secondarySkill->setLastTriggeredTime(popTime);
		
	m_lastHit = popTime - 1.f;
}

void Ship::dealDamage(Missile* missile, float time)
{
	m_health -= missile->getDamage();
	m_lastHit = time;
}

int Ship::getMaxHealth() const
{
	return ((ShipTemplate*) m_template)->getHealth();
}

int Ship::getExperienceValue() const
{
	return ((ShipTemplate*) m_template)->getExperienceValue();
}

void Ship::killedShip(Ship* ship)
{
	
}

} // entities
} // game



