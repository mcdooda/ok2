#ifndef GAME_LUA_LEVEL_H
#define GAME_LUA_LEVEL_H

#include "lua.h"

namespace game
{
namespace lua
{
namespace level
{

int load(lua_State* L, std::string filename);
bool resume(lua_State* L, int levelCoroutineRef);
void destroyState(lua_State* L, int levelCoroutineRef);

} // level
} // lua
} // game

#endif // GAME_LUA_LEVEL_H



