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

void pushEntity(lua_State* L, entities::Entity* entity);
entities::Entity* getEntity(lua_State* L, int index = 1);

// rotation
int l_Entity_setRotationZ(lua_State* L);
		
int l_Entity_getRotation(lua_State* L);
int l_Entity_getRotationX(lua_State* L);
int l_Entity_getRotationY(lua_State* L);
int l_Entity_getRotationZ(lua_State* L);
		
// position
int l_Entity_setPosition(lua_State* L);
int l_Entity_setPositionX(lua_State* L);
int l_Entity_setPositionY(lua_State* L);
		
int l_Entity_getPosition(lua_State* L);
int l_Entity_getPositionX(lua_State* L);
int l_Entity_getPositionY(lua_State* L);

} // lua
} // entities
} // game

#endif // GAME_ENTITIES_LUA_ENTITY_H



