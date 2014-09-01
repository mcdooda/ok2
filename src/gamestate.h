#ifndef GAME_GAMESTATE_H
#define GAME_GAMESTATE_H

#include <flat.h>

namespace game
{

class GameState : public flat::state::State
{
	public:
		virtual void enter(flat::state::Agent* agent);
		virtual void execute(flat::state::Agent* agent);
		virtual void exit(flat::state::Agent* agent);
};

}

#endif // GAME_GAMESTATE_H



