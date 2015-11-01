#ifndef GAME_ENTITIES_SHIP_H
#define GAME_ENTITIES_SHIP_H

#include "entity.h"
#include "missile.h"
#include "laser.h"
#include "../skills/skill.h"
#include "../skills/skilltemplate.h"
#include "../arena/arena.h"

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
		~Ship() override;
		
		void setTemplate(EntityTemplate* entityTemplate) override;
		
		bool update(Game* game, float time, float elapsedTime, arena::Arena* arena) override;
		
		void setPopTime(float popTime) override;
		
		bool isShip() const override { return true; }
		
		virtual void dealDamage(Missile* missile, float time);
		
		int getMaxHealth() const;
		inline int getHealth() const { return m_health; }
		inline bool isDead() const { return m_health <= 0; }
		
		int getExperienceValue() const;
		
		virtual void killedShip(Ship* ship);
		
	protected:
		void setTemplateSkills(unsigned int level = 1);
		void setSkill(skills::Skill*& skill, skills::SkillTemplate* skillTemplate);
		
	protected:
		skills::Skill* m_primarySkill;
		skills::Skill* m_secondarySkill;
		int m_health;
		float m_lastHit;
		std::set<Laser*> m_lasers;
};

} // entities
} // game

#endif // GAME_ENTITIES_SHIP_H



