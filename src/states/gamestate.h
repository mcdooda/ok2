#ifndef GAME_GAMESTATE_H
#define GAME_GAMESTATE_H

#include <flat.h>

#include "../entities/ship.h"
#include "../entities/shiptemplate.h"
#include "../entities/missile.h"
#include "../entities/missiletemplate.h"

namespace game
{
namespace states
{

class GameState : public flat::state::State
{
	public:
		virtual void enter(flat::state::Agent* agent);
		virtual void execute(flat::state::Agent* agent);
		virtual void exit(flat::state::Agent* agent);
		
		void addShipTemplate(entities::ShipTemplate* shipTemplate);
		void addMissileTemplate(entities::MissileTemplate* missileTemplate);
		void addSkillTemplate(skills::SkillTemplate* skillTemplate);
		
		skills::SkillTemplate* getSkillTemplate(const std::string& skillName);
		
		entities::Ship* addShip(const std::string& name, const flat::geometry::Vector2& position, float rotationZ, entities::Ship* ship1 = NULL);
		entities::Missile* addMissile(const std::string& name, const flat::geometry::Vector2& position, float rotationZ);
		
	private:
		void initMusic(Game* game);
		
		void loadLuaLibraries(Game* game);
		void loadTemplates(Game* game);
		
		void update(Game* game);
		void draw(Game* game);
		
	private:
		flat::audio::Music* m_music;
		
		std::map<std::string, entities::ShipTemplate*> m_shipTemplates;
		std::map<std::string, entities::MissileTemplate*> m_missileTemplates;
		std::map<std::string, skills::SkillTemplate*> m_skillTemplates;
		std::vector<entities::Ship*> m_ships;
		std::vector<entities::Missile*> m_missiles;
};

} // states
} // game

#endif // GAME_GAMESTATE_H



