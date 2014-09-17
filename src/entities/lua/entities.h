#ifndef GAME_ENTITIES_LUA_ENTITIES_H
#define GAME_ENTITIES_LUA_ENTITIES_H

#include <flat.h>
#include "../../states/gamestate.h"

namespace game
{
namespace entities
{
namespace lua
{

void open(lua_State* L, states::GameState* gameState);

int l_ship(lua_State* L);

} // lua
} // entities
} // game

#endif // GAME_ENTITIES_LUA_ENTITIES_H



