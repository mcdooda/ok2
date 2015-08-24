#include "time.h"

namespace game
{
namespace lua
{
namespace time
{

void open(lua_State* L, Game* game)
{
	const luaL_Reg funcs[] = {
		{"getTime", l_getTime},
		{nullptr, nullptr}
	};
	registerGameClosures(L, game, funcs);
}

int l_getTime(lua_State* L)
{
	Game* game = getGame(L);
	lua_pushnumber(L, game->time->getTime());
	return 1;
}

} // time
} // lua
} // game



