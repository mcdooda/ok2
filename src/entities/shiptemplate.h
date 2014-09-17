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
		
		void addSkillTemplates(skills::SkillTemplate* primarySkill, skills::SkillTemplate* secondarySkillName);
		
		skills::SkillTemplate* getPrimarySkillTemplate(unsigned int level);
		skills::SkillTemplate* getSecondarySkillTemplate(unsigned int level);
		
	private:
		std::vector<skills::SkillTemplate*> m_primarySkillTemplates;
		std::vector<skills::SkillTemplate*> m_secondarySkillTemplates;
};

} // entities
} // game

#endif // GAME_ENTITIES_SHIPTEMPLATE_H



