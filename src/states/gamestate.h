#ifndef GAME_GAMESTATE_H
#define GAME_GAMESTATE_H

#include <flat.h>

#include "../entities/entity.h"

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
		
		void storeShipTemplate(entities::EntityTemplate* shipTemplate);
		
	private:
		void initMusic(Game* game);
		
		void loadShips(Game* game);
		
		void update(Game* game);
		void draw(Game* game);
		
		void addShip(const std::string& name, const flat::geometry::Vector2& position);
		
	private:
		flat::audio::Music* m_music;
		
		std::map<std::string, entities::EntityTemplate*> m_templates;
		std::vector<entities::Entity*> m_entities;
};

} // states
} // game

#endif // GAME_GAMESTATE_H



