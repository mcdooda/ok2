#include "lua.h"

namespace game
{
namespace lua
{

void registerGameStateClosures(lua_State* L, states::GameState* gameState, const luaL_Reg* funcs)
{
	lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
	lua_pushlightuserdata(L, gameState);
	luaL_setfuncs(L, funcs, 1);
}

} // lua
} // game



