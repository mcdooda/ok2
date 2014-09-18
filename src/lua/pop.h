#ifndef GAME_LUA_POP_H
#define GAME_LUA_POP_H

#include "lua.h"

namespace game
{
namespace lua
{
namespace pop
{

void open(lua_State* L, states::GameState* gameState);

int l_popShip(lua_State* L);
int l_popMissile(lua_State* L);
int l_popShipMissiles(lua_State* L);

} // pop
} // lua
} // game

#endif // GAME_LUA_POP_H


