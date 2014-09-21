#ifndef GAME_ENTITIES_SHIP_H
#define GAME_ENTITIES_SHIP_H

#include "entity.h"
#include "../skills/skill.h"
#include "../skills/skilltemplate.h"

namespace game
{

namespace skills
{
class Skill;
}

namespace entities
{

class Ship : public Entity
{
	public:
		Ship();
		virtual ~Ship();
		
		virtual void setTemplate(EntityTemplate* entityTemplate);
		
		virtual void update(Game* game, float elapsedTime);
		
		virtual void setPopTime(float popTime);
		
	protected:
		void setTemplateSkills(unsigned int level = 1);
		void setSkill(skills::Skill*& skill, skills::SkillTemplate* skillTemplate);
		
	protected:
		skills::Skill* m_primarySkill;
		skills::Skill* m_secondarySkill;
};

} // entities
} // game

#endif // GAME_ENTITIES_SHIP_H



