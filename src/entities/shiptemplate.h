#ifndef GAME_ENTITIES_SHIPTEMPLATE_H
#define GAME_ENTITIES_SHIPTEMPLATE_H

#include "entitytemplate.h"
#include "../skills/skilltemplate.h"

namespace game
{
namespace entities
{

class ShipTemplate : public EntityTemplate
{
	public:
		ShipTemplate();
		virtual ~ShipTemplate();
		
		inline void setHealth(int health) { m_health = health; }
		inline int getHealth() const { return m_health; }
		
		inline void setExperienceValue(int experienceValue) { m_experienceValue = experienceValue; }
		inline int getExperienceValue() const { return m_experienceValue; }
		
		void addLevel(unsigned int levelExperience, skills::SkillTemplate* primarySkill, skills::SkillTemplate* secondarySkillName);
		
		unsigned int getMaxLevel() const;
		
		unsigned int getLevelExperience(unsigned int level) const;
		skills::SkillTemplate* getPrimarySkillTemplate(unsigned int level) const;
		skills::SkillTemplate* getSecondarySkillTemplate(unsigned int level) const;
		
	private:
		int m_health;
		unsigned int m_experienceValue;
		std::vector<skills::SkillTemplate*> m_primarySkillTemplates;
		std::vector<skills::SkillTemplate*> m_secondarySkillTemplates;
		std::vector<unsigned int> m_levelsExperience;
};

} // entities
} // game

#endif // GAME_ENTITIES_SHIPTEMPLATE_H



