#include "pop.h"
#include "../entities/lua/entity.h"

namespace game
{
namespace lua
{
namespace pop
{

void open(lua_State* L, states::GameState* gameState)
{
	const luaL_Reg funcs[] = {
		{"popShip",         l_popShip},
		{"popMissile",      l_popMissile},
		{"popShipMissiles", l_popShipMissiles},
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

int l_popShipMissiles(lua_State* L)
{
	entities::Entity* ship = entities::lua::getEntity(L);
	std::string name = luaL_checkstring(L, 2);
	int numMissiles = luaL_optint(L, 3, 1);
	float dx = luaL_optnumber(L, 4, 0);
	float dy = luaL_optnumber(L, 5, 0);
	float drz = luaL_optnumber(L, 6, 0);
	
	float shipRotationZ = ship->getRotation().getZ();
	const flat::geometry::Matrix4& shipModelMatrix = ship->getModelMatrix();
	
	states::GameState* gameState = (states::GameState*) lua_touserdata(L, lua_upvalueindex(1));
	
	for (int i = 0; i < numMissiles; i++)
	{
		flat::geometry::Vector2 position = shipModelMatrix * flat::geometry::Vector2(dx, -dy / 2 + (i / (numMissiles - 1)) * dy);
		float rotationZ = shipRotationZ - drz / 2 + (i / (numMissiles - 1)) * drz;
		gameState->addMissile(name, position, rotationZ);
	}
	
	return 0;
}
	
} // pop
} // lua
} // game



