#include "entities.h"
#include "../entity.h"

namespace game
{
namespace entities
{
namespace lua
{

void open(lua_State* L, states::GameState* gameState)
{
	// ship()
	lua_pushlightuserdata(L, gameState);
	lua_pushcclosure(L, l_ship, 1);
	lua_setglobal(L, "ship");
}
	
int l_ship(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TTABLE);
	
	lua_getfield(L, 1, "name");
	std::string name = luaL_checkstring(L, -1);
	
	lua_getfield(L, 1, "speed");
	float speed = luaL_checknumber(L, -1);
	
	lua_getfield(L, 1, "texture");
	std::string texture = luaL_checkstring(L, -1);
	
	lua_getfield(L, 1, "heightmap");
	std::string heightmap;
	if (!lua_isnil(L, -1))
	{
		heightmap = luaL_checkstring(L, -1);
	}
	
	lua_getfield(L, 1, "bumpmap");
	std::string bumpmap;
	if (!lua_isnil(L, -1))
	{
		bumpmap = luaL_checkstring(L, -1);
	}
	
	entities::EntityTemplate* shipTemplate = new entities::EntityTemplate();
	shipTemplate->setName(name);
	shipTemplate->setSpeed(speed);
	
	flat::util::Sprite* shipSprite;
	
	if (heightmap != "")
		shipSprite = new flat::util::HeightMap();
		
	else
		shipSprite = new flat::util::Sprite();
	
	shipSprite->setTexture(new flat::video::FileTexture(texture));
	
	if (heightmap != "")
	{
		((flat::util::HeightMap*) shipSprite)->setHeightMap(new flat::video::FileTexture(heightmap));
		
		if (bumpmap != "")
			((flat::util::HeightMap*) shipSprite)->setBumpMap(new flat::video::FileTexture(bumpmap));
	}
	
	shipTemplate->setSprite(shipSprite);
	
	states::GameState* gameState = (states::GameState*) lua_touserdata(L, lua_upvalueindex(1));
	gameState->storeShipTemplate(shipTemplate);
	
	return 0;
}

} // lua
} // entities
} // game



