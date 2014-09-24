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
		
		void addSkillTemplates(skills::SkillTemplate* primarySkill, skills::SkillTemplate* secondarySkillName);
		
		skills::SkillTemplate* getPrimarySkillTemplate(unsigned int level);
		skills::SkillTemplate* getSecondarySkillTemplate(unsigned int level);
		
	private:
		int m_health;
		std::vector<skills::SkillTemplate*> m_primarySkillTemplates;
		std::vector<skills::SkillTemplate*> m_secondarySkillTemplates;
};

} // entities
} // game

#endif // GAME_ENTITIES_SHIPTEMPLATE_H



