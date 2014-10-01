#include <iostream>
#include "../game.h"
#include "globalstate.h"

namespace game
{
namespace states
{

void GlobalState::enter(flat::state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	game->video->window->setTitle("Ocean's Keeper 2");
	game->video->window->hideCursor();
	
	resetViews(game);
	
	game->luaState = flat::lua::open();
}

void GlobalState::execute(flat::state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	
	if (game->input->keyboard->isJustPressed(K(ESCAPE)))
		game->stop();
		
	if (game->input->keyboard->isJustPressed(K(P)))
		game->time->togglePause();
		
	if (game->input->window->isResized())
		resetViews(game);
}

void GlobalState::exit(flat::state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	
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



