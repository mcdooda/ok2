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

void open(lua_State* L, Arena* arena, Game* game);

Arena* getArena(lua_State* L);
entities::Entity::Side checkSide(lua_State* L, int index);

int l_arena_getSize(lua_State* L);
int l_arena_getWidth(lua_State* L);
int l_arena_getHeight(lua_State* L);
int l_arena_getBounds(lua_State* L);

int l_arena_getPlayerPopPosition(lua_State* L);

int l_arena_getMissiles(lua_State* L);
int l_arena_getShips(lua_State* L);
int l_arena_getNumMissiles(lua_State* L);
int l_arena_getNumShips(lua_State* L);
int l_arena_getRandomPlayerShip(lua_State* L);

int l_arena_getEntityById(lua_State* L);

} // lua
} // arena
} // game

#endif // GAME_ARENA_LUA_ARENA_H



