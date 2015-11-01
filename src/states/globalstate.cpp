#include <iostream>
#include "../game.h"
#include "globalstate.h"

namespace game
{
namespace states
{

void GlobalState::enter(flat::state::Agent* agent)
{
	game::Game* game = agent->to<game::Game>();
	game->video->window->setTitle("Ocean's Keeper 2");
	//game->video->window->hideCursor();
	
	resetViews(game);
	
	game->luaState = flat::lua::open();
}

void GlobalState::execute(flat::state::Agent* agent)
{
	game::Game* game = agent->to<game::Game>();
		
	if (game->input->window->isResized())
		resetViews(game);
}

void GlobalState::exit(flat::state::Agent* agent)
{
	game::Game* game = agent->to<game::Game>();
	
	flat::lua::close(game->luaState);
}

void GlobalState::resetViews(game::Game* game)
{
	const flat::geometry::Vector2 windowSize = game->video->window->getSize();
	
	game->interfaceView.reset();
	game->interfaceView.move(windowSize / -2.0f);
	game->interfaceView.updateProjection(windowSize);
}

} // states
} // game



