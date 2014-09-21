#ifndef GAME_SKILLS_SKILL_H
#define GAME_SKILLS_SKILL_H

#include "../game.h"
#include "../entities/ship.h"
#include "skilltemplate.h"

namespace game
{

namespace entities
{
class Ship;
}

namespace skills
{

class Skill
{
	public:
		Skill(SkillTemplate* skillTemplate);
		virtual ~Skill();
		
		bool isReady(float time);
		float getRemainingCoolDownRatio(float time);
		
		void trigger(Game* game, entities::Ship* ship, float time);
		
		inline void setLastTriggeredTime(float lastTriggeredTime) { m_lastTriggeredTime = lastTriggeredTime; }
		
	protected:
		float m_lastTriggeredTime;
		SkillTemplate* m_template;
};

} // skills
} // game

#endif // GAME_SKILLS_SKILL_H



