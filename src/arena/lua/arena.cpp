#include "arena.h"
#include "../../entities/lua/entity.h"
#include "../../entities/playership.h"

namespace game
{
namespace arena
{
namespace lua
{

void open(lua_State* L, Arena* arena, Game* game)
{
	static const luaL_Reg arena_f[] = {
		{"getSize",              l_arena_getSize},
		{"getWidth",             l_arena_getWidth},
		{"getHeight",            l_arena_getHeight},
		{"getBounds",            l_arena_getBounds},
		
		{"getPlayerPopPosition", l_arena_getPlayerPopPosition},
		
		{"getMissiles",          l_arena_getMissiles},
		{"getShips",             l_arena_getShips},
		{"getNumMissiles",       l_arena_getNumMissiles},
		{"getNumShips",          l_arena_getNumShips},
		{"getRandomPlayerShip",  l_arena_getRandomPlayerShip},
		
		{"getEntityById",        l_arena_getEntityById},
		{nullptr, nullptr}
	};
	
	luaL_newlibtable(L, arena_f);
	
	// upvalue
	lua_pushlightuserdata(L, game);
	lua_pushlightuserdata(L, arena);
	
	luaL_setfuncs(L, arena_f, 2);
	lua_setglobal(L, "arena");
}

Game* getGame(lua_State* L)
{
	return (Game*) lua_touserdata(L, lua_upvalueindex(1));
}

Arena* getArena(lua_State* L)
{
	return (Arena*) lua_touserdata(L, lua_upvalueindex(2));
}

entities::Entity::Side checkSide(lua_State* L, int index)
{
	entities::Entity::Side side = (entities::Entity::Side) luaL_checkint(L, index);
	luaL_argcheck(L, side == entities::Entity::ALLY || side == entities::Entity::ENEMY, index, "invalid entity side");
	return side;
}

int l_arena_getSize(lua_State* L)
{
	Arena* arena = getArena(L);
	const flat::geometry::Vector2& size = arena->getSize();
	lua_pushnumber(L, size.x);
	lua_pushnumber(L, size.y);
	return 2;
}

int l_arena_getWidth(lua_State* L)
{
	Arena* arena = getArena(L);
	lua_pushnumber(L, arena->getSize().x);
	return 1;
}

int l_arena_getHeight(lua_State* L)
{
	Arena* arena = getArena(L);
	lua_pushnumber(L, arena->getSize().y);
	return 1;
}

int l_arena_getBounds(lua_State* L)
{
	Arena* arena = getArena(L);
	lua_pushnumber(L, arena->getMinX());
	lua_pushnumber(L, arena->getMinY());
	lua_pushnumber(L, arena->getMaxX());
	lua_pushnumber(L, arena->getMaxY());
	return 4;
}

int l_arena_getPlayerPopPosition(lua_State* L)
{
	Arena* arena = getArena(L);
	flat::geometry::Vector2 playerPopPosition = arena->getPlayerPopPosition();
	lua_pushnumber(L, playerPopPosition.x);
	lua_pushnumber(L, playerPopPosition.y);
	return 2;
}

int l_arena_getMissiles(lua_State* L)
{
	Arena* arena = getArena(L);
	entities::Entity::Side side = checkSide(L, 1);
	const std::set<entities::Missile*>& missiles = arena->getMissiles(side);
	lua_createtable(L, missiles.size(), 0);
	int i = 1;
	for (std::set<entities::Missile*>::iterator it = missiles.begin(); it != missiles.end(); it++)
	{
		entities::Missile* missile = *it;
		entities::lua::pushEntity(L, missile);
		lua_rawseti(L, -2, i);
		i++;
	}
	return 1;
}

int l_arena_getShips(lua_State* L)
{
	Arena* arena = getArena(L);
	entities::Entity::Side side = checkSide(L, 1);
	const std::set<entities::Ship*>& ships = arena->getShips(side);
	lua_createtable(L, ships.size(), 0);
	int i = 1;
	for (std::set<entities::Ship*>::iterator it = ships.begin(); it != ships.end(); it++)
	{
		entities::Ship* ship = *it;
		entities::lua::pushEntity(L, ship);
		lua_rawseti(L, -2, i);
		i++;
	}
	return 1;
}

int l_arena_getNumMissiles(lua_State* L)
{
	Arena* arena = getArena(L);
	entities::Entity::Side side = checkSide(L, 1);
	int numMissiles = arena->getNumMissiles(side);
	lua_pushinteger(L, numMissiles);
	return 1;
}

int l_arena_getNumShips(lua_State* L)
{
	Arena* arena = getArena(L);
	entities::Entity::Side side = checkSide(L, 1);
	int numShips = arena->getNumShips(side);
	lua_pushinteger(L, numShips);
	return 1;
}

int l_arena_getRandomPlayerShip(lua_State* L)
{
	Game* game = getGame(L);
	Arena* arena = getArena(L);
	entities::Entity::Side side = checkSide(L, 1);
	entities::PlayerShip* playerShip = arena->getRandomPlayerShip(side, game->random);
	entities::lua::pushEntity(L, playerShip);
	return 1;
}

int l_arena_getEntityById(lua_State* L)
{
	Arena* arena = getArena(L);
	int id = luaL_checkint(L, 1);
	entities::Entity* entity = arena->getEntityById(id);
	entities::lua::pushEntity(L, entity);
	return 1;
}

} // game
} // arena
} // lua



