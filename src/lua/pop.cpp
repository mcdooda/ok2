#include "pop.h"

namespace game
{
namespace lua
{
namespace pop
{

void open(lua_State* L, states::GameState* gameState)
{
	const luaL_Reg funcs[] = {
		{"popShip",    l_popShip},
		{"popMissile", l_popMissile},
		{NULL, NULL}
	};
	registerGameStateClosures(L, gameState, funcs);
}

int l_popShip(lua_State* L)
{
	std::string name = luaL_checkstring(L, 1);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float orientationZ = luaL_checknumber(L, 4);
	
	states::GameState* gameState = (states::GameState*) lua_touserdata(L, lua_upvalueindex(1));
	gameState->addShip(name, flat::geometry::Vector2(x, y), orientationZ);
	
	return 0;
}

int l_popMissile(lua_State* L)
{
	std::string name = luaL_checkstring(L, 1);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float orientationZ = luaL_checknumber(L, 4);
	
	states::GameState* gameState = (states::GameState*) lua_touserdata(L, lua_upvalueindex(1));
	gameState->addMissile(name, flat::geometry::Vector2(x, y), orientationZ);
	
	return 0;
}
	
} // pop
} // lua
} // game



