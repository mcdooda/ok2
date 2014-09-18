#ifndef GAME_LUA_TEMPLATES_H
#define GAME_LUA_TEMPLATES_H

#include "lua.h"
#include "../states/gamestate.h"

namespace game
{
namespace lua
{
namespace templates
{

void open(lua_State* L, states::GameState* gameState, Game* game);

int l_ship(lua_State* L);
int l_missile(lua_State* L);
int l_skill(lua_State* L);

} // templates
} // lua
} // game

#endif // GAME_ENTITIES_LUA_ENTITIES_H



