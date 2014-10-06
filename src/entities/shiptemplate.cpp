#include "shiptemplate.h"

namespace game
{
namespace entities
{

ShipTemplate::ShipTemplate() : EntityTemplate()
{

}

ShipTemplate::~ShipTemplate()
{

}

unsigned int ShipTemplate::getMaxLevel() const
{
	return m_levelsExperience.size();
}

void ShipTemplate::addLevel(unsigned int levelExperience, skills::SkillTemplate* primarySkillName, skills::SkillTemplate* secondarySkillName)
{
	m_levelsExperience.push_back(levelExperience);
	m_primarySkillTemplates.push_back(primarySkillName);
	m_secondarySkillTemplates.push_back(secondarySkillName);
}

unsigned int ShipTemplate::getLevelExperience(unsigned int level) const
{
	return m_levelsExperience[level - 1];
}

skills::SkillTemplate* ShipTemplate::getPrimarySkillTemplate(unsigned int level) const
{
	if (level - 1 < m_primarySkillTemplates.size())
		return m_primarySkillTemplates[level - 1];
		
	else if (!m_primarySkillTemplates.empty())
		return m_primarySkillTemplates.back();
		
	else
		return NULL;
}

skills::SkillTemplate* ShipTemplate::getSecondarySkillTemplate(unsigned int level) const
{
	if (level - 1 < m_secondarySkillTemplates.size())
		return m_secondarySkillTemplates[level - 1];
		
	else if (!m_secondarySkillTemplates.empty())
		return m_secondarySkillTemplates.back();
		
	else
		return NULL;
}

} // entities
} // game



