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
		
	private:
		void update(Game* game);
		void draw(Game* game);
		
	private:
		flat::audio::Music* m_music;
		
		std::vector<entities::Entity*> m_entities;
};

} // states
} // game

#endif // GAME_GAMESTATE_H



