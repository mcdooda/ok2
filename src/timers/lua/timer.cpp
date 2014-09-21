#include "timer.h"

namespace game
{
namespace timers
{
namespace lua
{

void open(lua_State* L, states::GameState* gameState, Game* game)
{
	// OK2.Timer metatable
	luaL_newmetatable(L, "OK2.Timer");
	
	// mt.__index = mt
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	
	static const luaL_Reg timer_m[] = {
		{"getDuration",    l_Timer_getDuration},
		{"getElapsedTime", l_Timer_getElapsedTime},
		{"getProgression", l_Timer_getProgression},
		{"stop",           l_Timer_stop},
		{"isStopped",      l_Timer_isStopped},
		{NULL, NULL}
	};
	
	luaL_setfuncs(L, timer_m, 0);
	
	static const luaL_Reg funcs[] = {
		{"timer", l_timer},
		{NULL, NULL}
	};
	game::lua::registerGameStateClosures(L, gameState, game, funcs);
	
	lua_pop(L, 1);
}

void pushTimer(lua_State* L, Timer* timer)
{
	Timer** timerPointer = (Timer**) lua_newuserdata(L, sizeof(Timer*));
	*timerPointer = timer;
	luaL_getmetatable(L, "OK2.Timer");
	lua_setmetatable(L, -2);
}

Timer* getTimer(lua_State* L, int index)
{
	return *(Timer**) luaL_checkudata(L, index, "OK2.Timer");;
}

void triggerTimerUpdateFunction(lua_State* L, Timer* timer)
{
	int updateFunctionRef = timer->getUpdateFunctionRef();
	if (updateFunctionRef != LUA_NOREF)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, updateFunctionRef);
		pushTimer(L, timer);
		lua_call(L, 1, 0);
	}
}

void triggerTimerEndFunction(lua_State* L, Timer* timer)
{
	int endFunctionRef = timer->getEndFunctionRef();
	if (endFunctionRef != LUA_NOREF)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, endFunctionRef);
		pushTimer(L, timer);
		lua_call(L, 1, 0);
	}
}

int l_timer(lua_State* L)
{
	float duration = luaL_checknumber(L, 1);
	
	int updateFunctionRef = LUA_NOREF;
	if (lua_type(L, 2) == LUA_TFUNCTION)
	{
		lua_pushvalue(L, 2);
		updateFunctionRef = luaL_ref(L, LUA_REGISTRYINDEX);
	}
	
	int endFunctionRef = LUA_NOREF;
	if (lua_type(L, 3) == LUA_TFUNCTION)
	{
		lua_pushvalue(L, 3);
		endFunctionRef = luaL_ref(L, LUA_REGISTRYINDEX);
	}
	
	Timer* timer = new Timer();
	timer->setDuration(duration);
	timer->setUpdateFunctionRef(updateFunctionRef);
	timer->setEndFunctionRef(endFunctionRef);
	
	Game* game = (Game*) lua_touserdata(L, lua_upvalueindex(2));
	timer->setBeginTime(game->time->getTime());
	
	states::GameState* gameState = (states::GameState*) lua_touserdata(L, lua_upvalueindex(1));
	gameState->addTimer(timer);
	
	return 0;
}

int l_Timer_getDuration(lua_State* L)
{
	Timer* timer = getTimer(L);
	lua_pushnumber(L, timer->getDuration());
	return 1;
}

int l_Timer_getElapsedTime(lua_State* L)
{
	Timer* timer = getTimer(L);
	lua_pushnumber(L, timer->getElapsedTime());
	return 1;
}

int l_Timer_getProgression(lua_State* L)
{
	Timer* timer = getTimer(L);
	lua_pushnumber(L, timer->getProgression());
	return 1;
}

int l_Timer_stop(lua_State* L)
{
	Timer* timer = getTimer(L);
	timer->stop();
	return 0;
}

int l_Timer_isStopped(lua_State* L)
{
	Timer* timer = getTimer(L);
	lua_pushboolean(L, timer->isStopped());
	return 1;
}

} // lua
} // timers
} // game


