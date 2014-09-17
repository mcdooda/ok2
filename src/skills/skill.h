#ifndef GAME_SKILLS_SKILL_H
#define GAME_SKILLS_SKILL_H

#include "../game.h"

namespace game
{
namespace skills
{

class Skill
{
	public:
		Skill();
		virtual ~Skill();
		
		bool isReady(float time);
		float getRemainingCoolDownRatio(float time);
		
		inline float getCoolDown() const { return m_coolDown; }
		inline void setCoolDown(float coolDown) { m_coolDown = coolDown; }
		
		virtual void trigger(Game* game, float time);
		
	protected:
		float m_coolDown;
		float m_lastTriggered;
};

} // skills
} // game

#endif // GAME_SKILLS_SKILL_H



