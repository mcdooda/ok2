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

void registerGameStateClosures(lua_State* L, Game* game, states::GameState* gameState, const luaL_Reg* funcs)
{
	lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
	lua_pushlightuserdata(L, game);
	lua_pushlightuserdata(L, gameState);
	luaL_setfuncs(L, funcs, 2);
}

Game* getGame(lua_State* L)
{
	return static_cast<Game*>(lua_touserdata(L, lua_upvalueindex(1)));
}

states::GameState* getGameState(lua_State* L)
{
	return static_cast<states::GameState*>(lua_touserdata(L, lua_upvalueindex(2)));
}

} // lua
} // game



