#ifndef GAME_TIMER_LUA_TIMER_H
#define GAME_TIMER_LUA_TIMER_H

#include "../../lua/lua.h"

namespace game
{
namespace timers
{
namespace lua
{

void open(lua_State* L, states::GameState* gameState, Game* game);

void pushTimer(lua_State* L, Timer* timer);
Timer* getTimer(lua_State* L, int index = 1);

Game* getGame(lua_State* L);
states::GameState* getGameState(lua_State* L);

void triggerTimerUpdateFunction(lua_State* L, Timer* timer);
void triggerTimerEndFunction(lua_State* L, Timer* timer);

void destroyTimerState(lua_State* L, Timer* timer);

int l_timer(lua_State* L);

int l_Timer_getDuration(lua_State* L);
int l_Timer_getElapsedTime(lua_State* L);
int l_Timer_getProgression(lua_State* L);
int l_Timer_stop(lua_State* L);
int l_Timer_isStopped(lua_State* L);

} // lua
} // timers
} // game

#endif // GAME_TIMER_LUA_TIMER_H



