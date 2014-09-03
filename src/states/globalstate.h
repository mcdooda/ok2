#ifndef GAME_GLOBALSTATE_H
#define GAME_GLOBALSTATE_H

#include <flat.h>

#include "../game.h"

namespace game
{
namespace states
{

class GlobalState : public flat::state::State
{
	public:
		virtual void enter(flat::state::Agent* agent);
		virtual void execute(flat::state::Agent* agent);
		virtual void exit(flat::state::Agent* agent);
		
	private:
		void resetViews(game::Game* game);
};

} // states
} // game

#endif // GAME_GLOBALSTATE_H



