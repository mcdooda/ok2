#include <flat.h>

#include "game.h"
#include "states/globalstate.h"
#include "states/menustate.h"

namespace game
{

Game::Game(const std::vector<std::string>& args) : flat::Game(args)
{
	getStateMachine()->setGlobalState(new states::GlobalState());
	getStateMachine()->setState(new states::MenuState());
}

Game::~Game()
{
	
}

void Game::openWindow()
{
	video->window->open(video->window->getDesktopSize() / 2, false, true);
}

} // game



