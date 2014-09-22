#include "arena.h"

namespace game
{
namespace arena
{
namespace lua
{

void open(lua_State* L, Arena* arena)
{
	static const luaL_Reg arena_f[] = {
		{"getSize",   l_arena_getSize},
		{"getWidth",  l_arena_getWidth},
		{"getHeight", l_arena_getHeight},
		{"getBounds", l_arena_getBounds},
		{NULL, NULL}
	};
	
	luaL_newlibtable(L, arena_f);
	
	// upvalue
	lua_pushlightuserdata(L, arena);
	
	luaL_setfuncs(L, arena_f, 1);
	lua_setglobal(L, "arena");
}

int l_arena_getSize(lua_State* L)
{
	Arena* arena = (Arena*) lua_touserdata(L, lua_upvalueindex(1));
	const flat::geometry::Vector2& size = arena->getSize();
	lua_pushnumber(L, size.getX());
	lua_pushnumber(L, size.getY());
	return 2;
}

int l_arena_getWidth(lua_State* L)
{
	Arena* arena = (Arena*) lua_touserdata(L, lua_upvalueindex(1));
	lua_pushnumber(L, arena->getSize().getX());
	return 1;
}

int l_arena_getHeight(lua_State* L)
{
	Arena* arena = (Arena*) lua_touserdata(L, lua_upvalueindex(1));
	lua_pushnumber(L, arena->getSize().getY());
	return 1;
}

int l_arena_getBounds(lua_State* L)
{
	Arena* arena = (Arena*) lua_touserdata(L, lua_upvalueindex(1));
	lua_pushnumber(L, arena->getMinX());
	lua_pushnumber(L, arena->getMinY());
	lua_pushnumber(L, arena->getMaxX());
	lua_pushnumber(L, arena->getMaxY());
	return 4;
}

} // game
} // arena
} // lua
