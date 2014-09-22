#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <flat/game.h>

namespace game
{

class Game : public flat::Game
{
	public:
		Game(const std::vector<std::string>& args);
		virtual ~Game();
		
	public:
		// view
		flat::video::View interfaceView;
		
		// lua
		lua_State* luaState;
};

} // game

#endif // GAME_GAME_H



