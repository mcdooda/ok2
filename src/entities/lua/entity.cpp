#include <iostream>
#include "entity.h"
#include "../playership.h"

namespace game
{
namespace entities
{
namespace lua
{

void open(lua_State* L)
{
	// OK2.Ship metatable
	luaL_newmetatable(L, "OK2.Ship");
	
	// mt.__index = mt
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	
	static const luaL_Reg entitylib_m[] = {
		// rotation
		{"setRotationZ",        l_Entity_setRotationZ},
		
		{"getRotation",         l_Entity_getRotation},
		{"getRotationX",        l_Entity_getRotationX},
		{"getRotationY",        l_Entity_getRotationY},
		{"getRotationZ",        l_Entity_getRotationZ},
		
		{"follow",              l_Entity_follow},
		
		// position
		{"setPosition",         l_Entity_setPosition},
		{"setPositionX",        l_Entity_setPositionX},
		{"setPositionY",        l_Entity_setPositionY},
		
		{"getPosition",         l_Entity_getPosition},
		{"getPositionX",        l_Entity_getPositionX},
		{"getPositionY",        l_Entity_getPositionY},
		
		{"getAbsolutePosition", l_Entity_getAbsolutePosition},
		
		// speed
		{"getSpeed",            l_Entity_getSpeed},
		{"getSpeedX",           l_Entity_getSpeedX},
		{"getSpeedY",           l_Entity_getSpeedY},
		
		// misc
		{"getSide",             l_Entity_getSide},
		{"getId",               l_Entity_getId},
		{"getPopTime",          l_Entity_getPopTime},
		{"getNumLives",         l_Entity_getNumLives},
		
		// lua data
		{"data",                l_Entity_data},
		
		{nullptr, nullptr}
	};
	
	luaL_setfuncs(L, entitylib_m, 0);
	
	lua_pop(L, 1);
}

void pushEntity(lua_State* L, Entity* entity)
{
	if (entity != nullptr)
	{
		Entity** entityPointer = (Entity**) lua_newuserdata(L, sizeof(Entity*));
		*entityPointer = entity;
		luaL_getmetatable(L, "OK2.Ship");
		lua_setmetatable(L, -2);
	}
	else
		lua_pushnil(L);
}

Entity* getEntity(lua_State* L, int index)
{
	return *(Entity**) luaL_checkudata(L, index, "OK2.Ship");
}

void initEntity(lua_State* L, Entity* entity, float time)
{
	createEntityData(L, entity);
	triggerEntityPopFunction(L, entity, time);
}

void createEntityData(lua_State* L, Entity* entity)
{
	lua_newtable(L);
	int dataRef = luaL_ref(L, LUA_REGISTRYINDEX);
	entity->setDataRef(dataRef);
}

void triggerEntityPopFunction(lua_State* L, Entity* entity, float time)
{
	int popFunctionRef = entity->getPopFunctionRef();
	if (popFunctionRef != LUA_NOREF)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, popFunctionRef);
		pushEntity(L, entity);
		lua_pushnumber(L, time);
		lua_call(L, 2, 0);
	}
}

void triggerEntityUpdateFunction(lua_State* L, Entity* entity, float time, float elapsedTime)
{
	int updateFunctionRef = entity->getUpdateFunctionRef();
	if (updateFunctionRef != LUA_NOREF)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, updateFunctionRef);
		pushEntity(L, entity);
		lua_pushnumber(L, time);
		lua_pushnumber(L, elapsedTime);
		lua_call(L, 3, 0);
	}
}

void destroyEntityState(lua_State* L, Entity* entity)
{
	luaL_unref(L, LUA_REGISTRYINDEX, entity->getDataRef());
}

int l_Entity_setRotationZ(lua_State* L)
{
	Entity* entity = getEntity(L);
	float rotationZ = luaL_checknumber(L, 2);
	entity->setRotationZ(rotationZ);
	return 0;
}
		
int l_Entity_getRotation(lua_State* L)
{
	Entity* entity = getEntity(L);
	const flat::geometry::Vector3& rotation = entity->getRotation();
	lua_pushnumber(L, rotation.x);
	lua_pushnumber(L, rotation.y);
	lua_pushnumber(L, rotation.z);
	return 3;
}

int l_Entity_getRotationX(lua_State* L)
{
	Entity* entity = getEntity(L);
	const flat::geometry::Vector3& rotation = entity->getRotation();
	lua_pushnumber(L, rotation.x);
	return 1;
}

int l_Entity_getRotationY(lua_State* L)
{
	Entity* entity = getEntity(L);
	const flat::geometry::Vector3& rotation = entity->getRotation();
	lua_pushnumber(L, rotation.y);
	return 1;
}

int l_Entity_getRotationZ(lua_State* L)
{
	Entity* entity = getEntity(L);
	const flat::geometry::Vector3& rotation = entity->getRotation();
	lua_pushnumber(L, rotation.z);
	return 1;
}

int l_Entity_follow(lua_State* L)
{
	Entity* entity = getEntity(L);
	Entity* entity2 = getEntity(L, 2);
	entity->follow(entity2);
	return 0;
}

int l_Entity_setPosition(lua_State* L)
{
	Entity* entity = getEntity(L);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	entity->setPosition(flat::geometry::Vector2(x, y));
	return 0;
}

int l_Entity_setPositionX(lua_State* L)
{
	Entity* entity = getEntity(L);
	float x = luaL_checknumber(L, 2);
	entity->setPositionX(x);
	return 0;
}

int l_Entity_setPositionY(lua_State* L)
{
	Entity* entity = getEntity(L);
	float y = luaL_checknumber(L, 2);
	entity->setPositionY(y);
	return 0;
}
		
int l_Entity_getPosition(lua_State* L)
{
	Entity* entity = getEntity(L);
	const flat::geometry::Vector2& position = entity->getPosition();
	lua_pushnumber(L, position.x);
	lua_pushnumber(L, position.y);
	return 2;
}

int l_Entity_getPositionX(lua_State* L)
{
	Entity* entity = getEntity(L);
	const flat::geometry::Vector2& position = entity->getPosition();
	lua_pushnumber(L, position.x);
	return 1;
}

int l_Entity_getPositionY(lua_State* L)
{
	Entity* entity = getEntity(L);
	const flat::geometry::Vector2& position = entity->getPosition();
	lua_pushnumber(L, position.y);
	return 1;
}

int l_Entity_getAbsolutePosition(lua_State* L)
{
	Entity* entity = getEntity(L);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	flat::geometry::Vector2 relativePosition(x, y);
	flat::geometry::Vector2 absolutePosition = entity->getAbsolutePosition(relativePosition);
	lua_pushnumber(L, absolutePosition.x);
	lua_pushnumber(L, absolutePosition.y);
	return 2;
}

int l_Entity_getSpeed(lua_State* L)
{
	Entity* entity = getEntity(L);
	const flat::geometry::Vector2& speed = entity->getSpeed();
	lua_pushnumber(L, speed.x);
	lua_pushnumber(L, speed.y);
	return 2;
}

int l_Entity_getSpeedX(lua_State* L)
{
	Entity* entity = getEntity(L);
	const flat::geometry::Vector2& speed = entity->getSpeed();
	lua_pushnumber(L, speed.x);
	return 1;
}

int l_Entity_getSpeedY(lua_State* L)
{
	Entity* entity = getEntity(L);
	const flat::geometry::Vector2& speed = entity->getSpeed();
	lua_pushnumber(L, speed.y);
	return 1;
}

int l_Entity_getSide(lua_State* L)
{
	Entity* entity = getEntity(L);
	lua_pushinteger(L, entity->getSide());
	return 1;
}

int l_Entity_getId(lua_State* L)
{
	Entity* entity = getEntity(L);
	lua_pushinteger(L, entity->getId());
	return 1;
}

int l_Entity_getPopTime(lua_State* L)
{
	Entity* entity = getEntity(L);
	lua_pushnumber(L, entity->getPopTime());
	return 1;
}

int l_Entity_getNumLives(lua_State* L)
{
	Entity* entity = getEntity(L);
	unsigned int numLives = 1;
	if (PlayerShip* playerShip = dynamic_cast<PlayerShip*>(entity))
	{
		numLives = playerShip->getNumLives();
	}
	lua_pushunsigned(L, numLives);
	return 1;
}

int l_Entity_data(lua_State* L)
{
	Entity* entity = getEntity(L);
	lua_rawgeti(L, LUA_REGISTRYINDEX, entity->getDataRef());
	return 1;
}

} // lua
} // entities
} // game



