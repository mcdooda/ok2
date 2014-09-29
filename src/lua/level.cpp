#include <iostream>
#include "level.h"

namespace game
{
namespace lua
{
namespace level
{

int load(lua_State* L, std::string filename)
{
	lua_State* L1 = lua_newthread(L);
	luaL_loadfile(L1, filename.c_str());
	int status = lua_resume(L1, L, 0);
	
	if (status != LUA_YIELD && status != LUA_OK)
	{
		std::cout << "invalid thread status 1: " << flat::lua::codeToString(status) << std::endl;
		lua_error(L1);
	}
	
	return luaL_ref(L, LUA_REGISTRYINDEX);
}

bool resume(lua_State* L, int levelCoroutineRef)
{
	if (levelCoroutineRef != LUA_NOREF)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, levelCoroutineRef);
		lua_State* L1 = lua_tothread(L, -1);
		lua_pop(L, 1);
		
		int status = lua_resume(L1, L, 0);
	
		if (status != LUA_YIELD && status != LUA_OK)
		{
			std::cout << "invalid thread status 2: " << flat::lua::codeToString(status) << std::endl;
			flat::lua::printStack(L);
			lua_error(L1);
		}
		
		return status == LUA_OK;
	}
	else
		return true;
}

void destroyLevelState(lua_State* L, int levelCoroutineRef)
{
	luaL_unref(L, LUA_REGISTRYINDEX, levelCoroutineRef);
}

} // level
} // lua
} // game



