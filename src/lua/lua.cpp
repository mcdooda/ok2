#include "lua.h"

namespace game
{
namespace lua
{

void registerGameClosures(lua_State* L, Game* game, const luaL_Reg* funcs)
{
	lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
	lua_pushlightuserdata(L, game);
	luaL_setfuncs(L, funcs, 1);
}

void registerGameStateClosures(lua_State* L, states::GameState* gameState, Game* game, const luaL_Reg* funcs)
{
	lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
	lua_pushlightuserdata(L, gameState);
	lua_pushlightuserdata(L, game);
	luaL_setfuncs(L, funcs, 2);
}

} // lua
} // game



