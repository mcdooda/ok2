#ifndef GAME_LUA_LUA_H
#define GAME_LUA_LUA_H

#include <flat.h>
#include "../states/gamestate.h"

namespace game
{
namespace states
{
class GameState;
}

namespace lua
{

void registerGameClosures(lua_State* L, Game* game, const luaL_Reg* funcs);
void registerGameStateClosures(lua_State* L, Game* game, states::GameState* gameState, const luaL_Reg* funcs);

Game* getGame(lua_State* L);
states::GameState* getGameState(lua_State* L);

} // lua
} // game

#endif // GAME_LUA_LUA_H



