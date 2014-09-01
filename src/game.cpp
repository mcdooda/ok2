#include <flat.h>

#include "game.h"
#include "globalstate.h"
#include "menustate.h"

namespace game
{

Game::Game(const std::vector<std::string>& args) : flat::Game(args)
{
	getStateMachine()->setGlobalState(new GlobalState());
	getStateMachine()->setState(new MenuState());
}

Game::~Game()
{
	
}

} // game



