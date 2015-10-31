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
		void enter(flat::state::Agent* agent) override;
		void execute(flat::state::Agent* agent) override;
		void exit(flat::state::Agent* agent) override;
		
	private:
		void resetViews(game::Game* game);
		
		void loadGame(game::Game* game);
		void loadShips(game::Game* game);
};

} // states
} // game

#endif // GAME_GLOBALSTATE_H



