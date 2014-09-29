#ifndef GAME_ENTITIES_LUA_ENTITY_H
#define GAME_ENTITIES_LUA_ENTITY_H

#include "../../lua/lua.h"

namespace game
{
namespace entities
{
namespace lua
{

void open(lua_State* L);

void pushEntity(lua_State* L, Entity* entity);
Entity* getEntity(lua_State* L, int index = 1);

void initEntity(lua_State* L, Entity* entity, float time);
void createEntityData(lua_State* L, Entity* entity);
void triggerEntityPopFunction(lua_State* L, Entity* entity, float time);
void triggerEntityUpdateFunction(lua_State* L, Entity* entity, float time, float elapsedTime);

void destroyEntityState(lua_State* L, Entity* entity);

// rotation
int l_Entity_setRotationZ(lua_State* L);
		
int l_Entity_getRotation(lua_State* L);
int l_Entity_getRotationX(lua_State* L);
int l_Entity_getRotationY(lua_State* L);
int l_Entity_getRotationZ(lua_State* L);

int l_Entity_follow(lua_State* L);
		
// position
int l_Entity_setPosition(lua_State* L);
int l_Entity_setPositionX(lua_State* L);
int l_Entity_setPositionY(lua_State* L);
		
int l_Entity_getPosition(lua_State* L);
int l_Entity_getPositionX(lua_State* L);
int l_Entity_getPositionY(lua_State* L);

int l_Entity_getAbsolutePosition(lua_State* L);

// speed
int l_Entity_getSpeed(lua_State* L);
int l_Entity_getSpeedX(lua_State* L);
int l_Entity_getSpeedY(lua_State* L);

// misc
int l_Entity_getSide(lua_State* L);
int l_Entity_getId(lua_State* L);
int l_Entity_getPopTime(lua_State* L);

// lua data
int l_Entity_data(lua_State* L);

} // lua
} // entities
} // game

#endif // GAME_ENTITIES_LUA_ENTITY_H



