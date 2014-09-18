#ifndef GAME_SKILLS_SKILLTEMPLATE_H
#define GAME_SKILLS_SKILLTEMPLATE_H

#include <string>

namespace game
{
namespace skills
{

class SkillTemplate
{
	public:
		SkillTemplate();
		virtual ~SkillTemplate();
		
		inline void setName(const std::string& name) { m_name = name; }
		inline const std::string& getName() const { return m_name; }
		
		inline void setCooldown(float cooldown) { m_cooldown = cooldown; }
		inline float getCooldown() const { return m_cooldown; }
		
		inline void setTriggerFunctionRef(int triggerFunctionRef) { m_triggerFunctionRef = triggerFunctionRef; }
		inline int getTriggerFunctionRef() const { return m_triggerFunctionRef; }
		
	protected:
		std::string m_name;
		float m_cooldown;
		int m_triggerFunctionRef;
};

} // skills
} // game

#endif // GAME_SKILLS_SKILLTEMPLATE_H



