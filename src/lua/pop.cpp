#include "pop.h"
#include "../entities/lua/entity.h"
#include "../entities/playership.h"

namespace game
{
namespace lua
{
namespace pop
{

void open(lua_State* L, states::GameState* gameState, Game* game)
{
	const luaL_Reg funcs[] = {
		{"popShip",         l_popShip},
		{"popMissile",      l_popMissile},
		{"popShipMissiles", l_popShipMissiles},
		{NULL, NULL}
	};
	registerGameStateClosures(L, gameState, game, funcs);
	
	lua_pushinteger(L, entities::Entity::ALLY);
	lua_setglobal(L, "ALLY");
	
	lua_pushinteger(L, entities::Entity::ENEMY);
	lua_setglobal(L, "ENEMY");
}

entities::Entity::Side checkSide(lua_State* L, int index)
{
	entities::Entity::Side side = (entities::Entity::Side) luaL_checkint(L, index);
	luaL_argcheck(L, side == entities::Entity::ALLY || side == entities::Entity::ENEMY, index, "invalid entity side");
	return side;
}

int l_popShip(lua_State* L)
{
	std::string name = luaL_checkstring(L, 1);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float rotationZ = luaL_checknumber(L, 4);
	entities::Entity::Side side = checkSide(L, 5);
	int isPlayerShip = lua_toboolean(L, 6);
	
	states::GameState* gameState = (states::GameState*) lua_touserdata(L, lua_upvalueindex(1));
	Game* game = (Game*) lua_touserdata(L, lua_upvalueindex(2));
	float time = game->time->getTime();
	
	entities::Ship* ship = NULL;
	if (isPlayerShip)
		ship = new entities::PlayerShip();
	
	ship = gameState->addShip(name, flat::geometry::Vector2(x, y), rotationZ, side, ship);
	ship->setPopTime(time);
	entities::lua::initEntity(L, ship, time);
	
	entities::lua::pushEntity(L, ship);
	
	return 1;
}

int l_popMissile(lua_State* L)
{
	std::string name = luaL_checkstring(L, 1);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float rotationZ = luaL_checknumber(L, 4);
	entities::Entity::Side side = checkSide(L, 5);
	
	states::GameState* gameState = (states::GameState*) lua_touserdata(L, lua_upvalueindex(1));
	Game* game = (Game*) lua_touserdata(L, lua_upvalueindex(2));
	float time = game->time->getTime();
	
	entities::Missile* missile = gameState->addMissile(name, flat::geometry::Vector2(x, y), rotationZ, side);
	missile->setPopTime(time);
	entities::lua::initEntity(L, missile, time);
	
	entities::lua::pushEntity(L, missile);
	
	return 1;
}

int l_popShipMissiles(lua_State* L)
{
	entities::Entity* ship = entities::lua::getEntity(L);
	std::string name = luaL_checkstring(L, 2);
	int numMissiles = luaL_optint(L, 3, 1);
	float dx = luaL_optnumber(L, 4, 0);
	float dy = luaL_optnumber(L, 5, 0);
	float drz = luaL_optnumber(L, 6, 0);
	
	entities::Entity::Side side = ship->getSide();
	
	float shipRotationZ = ship->getRotation().getZ();
	const flat::geometry::Matrix4& shipModelMatrix = ship->getModelMatrix();
	
	states::GameState* gameState = (states::GameState*) lua_touserdata(L, lua_upvalueindex(1));
	Game* game = (Game*) lua_touserdata(L, lua_upvalueindex(2));
	float time = game->time->getTime();
	
	if (numMissiles == 1)
	{
		flat::geometry::Vector2 position = shipModelMatrix * flat::geometry::Vector2(dx, dy);
		float rotationZ = shipRotationZ + drz;
		entities::Missile* missile = gameState->addMissile(name, position, rotationZ, side);
		entities::lua::initEntity(L, missile, time);
	}
	else if (numMissiles > 1)
	{
		for (int i = 0; i < numMissiles; i++)
		{
			flat::geometry::Vector2 position = shipModelMatrix * flat::geometry::Vector2(dx, -dy / 2 + ((float) i / (numMissiles - 1)) * dy);
			float rotationZ = shipRotationZ - drz / 2 + ((float) i / (numMissiles - 1)) * drz;
			entities::Missile* missile = gameState->addMissile(name, position, rotationZ, side);
			entities::lua::initEntity(L, missile, time);
		}
	}
	
	return 0;
}
	
} // pop
} // lua
} // game



