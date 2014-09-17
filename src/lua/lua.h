#ifndef GAME_LUA_LUA_H
#define GAME_LUA_LUA_H

#include <flat.h>
#include "../states/gamestate.h"

namespace game
{
namespace lua
{

void registerGameStateClosures(lua_State* L, states::GameState* gameState, const luaL_Reg* funcs);

} // lua
} // game

#endif // GAME_LUA_LUA_H



