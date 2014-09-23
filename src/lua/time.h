#ifndef GAME_LUA_TIME_H
#define GAME_LUA_TIME_H

#include "lua.h"

namespace game
{
namespace lua
{
namespace time
{

void open(lua_State* L, Game* game);

Game* getGame(lua_State* L);

int l_getTime(lua_State* L);

} // time
} // lua
} // game

#endif // GAME_LUA_TIME_H



