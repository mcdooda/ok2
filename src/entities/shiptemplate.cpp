#include "shiptemplate.h"

namespace game
{
namespace entities
{

ShipTemplate::ShipTemplate()
{

}

ShipTemplate::~ShipTemplate()
{

}

void ShipTemplate::addSkillTemplates(skills::SkillTemplate* primarySkillName, skills::SkillTemplate* secondarySkillName)
{
	m_primarySkillTemplates.push_back(primarySkillName);
	m_secondarySkillTemplates.push_back(secondarySkillName);
}

skills::SkillTemplate* ShipTemplate::getPrimarySkillTemplate(unsigned int level)
{
	if (level - 1 < m_primarySkillTemplates.size())
		return m_primarySkillTemplates[level - 1];
		
	else
		return m_primarySkillTemplates.back();
}

skills::SkillTemplate* ShipTemplate::getSecondarySkillTemplate(unsigned int level)
{
	if (level - 1 < m_secondarySkillTemplates.size())
		return m_secondarySkillTemplates[level - 1];
		
	else
		return m_secondarySkillTemplates.back();
}

} // entities
} // game



