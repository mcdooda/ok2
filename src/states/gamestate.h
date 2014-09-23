#ifndef GAME_GAMESTATE_H
#define GAME_GAMESTATE_H

#include <set>
#include <flat.h>

#include "../entities/ship.h"
#include "../entities/shiptemplate.h"
#include "../entities/missile.h"
#include "../entities/missiletemplate.h"
#include "../timers/timer.h"
#include "../arena/arena.h"

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
		
		entities::Ship* addShip(const std::string& name, const flat::geometry::Vector2& position, float rotationZ, entities::Entity::Side side, entities::Ship* ship1 = NULL);
		entities::Missile* addMissile(const std::string& name, const flat::geometry::Vector2& position, float rotationZ, entities::Entity::Side side);
		
		void addTimer(timers::Timer* timer);
		
	private:
		void initMusic(Game* game);
		void initGraphics(Game* game);
		
		void loadLuaLibraries(Game* game);
		void loadTemplates(Game* game);
		
		void loadLevel(Game* game);
		void updateLevel(Game* game);
		
		void update(Game* game);
		void draw(Game* game);
		
		void updateTimers(Game* game);
		
	private:
		// entity and skill templates
		std::map<std::string, entities::ShipTemplate*> m_shipTemplates;
		std::map<std::string, entities::MissileTemplate*> m_missileTemplates;
		std::map<std::string, skills::SkillTemplate*> m_skillTemplates;
		
		// ARENA
		arena::Arena* m_arena;
		int m_levelCoroutineRef;
		
		// GRAPHICS
		
		// view
		flat::video::View m_view;
		
		// passes
		flat::video::FrameBuffer m_frameBuffer;
		flat::video::Pass m_heightMapPass;
		flat::video::Pass m_spritePass;
		flat::video::Render m_renderProgram;
		
		// attributes & uniforms
		flat::util::RenderSettings m_heightMapRenderSettings;
		flat::util::RenderSettings m_spriteRenderSettings;
		flat::video::Uniform m_arenaSizeUniform;
		flat::video::Uniform m_screenSizeUniform;
		
		// AUDIO
		flat::audio::Music* m_music;
		
		// TIMERS
		std::set<timers::Timer*> m_timers;
};

} // states
} // game

#endif // GAME_GAMESTATE_H



