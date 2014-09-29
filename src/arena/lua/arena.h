#ifndef GAME_ARENA_LUA_ARENA_H
#define GAME_ARENA_LUA_ARENA_H

#include "../../lua/lua.h"
#include "../arena.h"

namespace game
{
namespace arena
{
namespace lua
{

void open(lua_State* L, Arena* arena);

int l_arena_getSize(lua_State* L);
int l_arena_getWidth(lua_State* L);
int l_arena_getHeight(lua_State* L);
int l_arena_getBounds(lua_State* L);
int l_arena_getPlayerPopPosition(lua_State* L);

} // lua
} // arena
} // game

#endif // GAME_ARENA_LUA_ARENA_H



