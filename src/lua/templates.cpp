#include "templates.h"
#include "../entities/shiptemplate.h"

namespace game
{
namespace lua
{
namespace templates
{

void open(lua_State* L, states::GameState* gameState)
{
	const luaL_Reg funcs[] = {
		{"ship",    l_ship},
		{"missile", l_missile},
		{"skill",   l_skill},
		{NULL, NULL}
	};
	registerGameStateClosures(L, gameState, funcs);
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
	
	entities::ShipTemplate* shipTemplate = new entities::ShipTemplate();
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
	
	lua_getfield(L, 1, "skills");
	luaL_checktype(L, -1, LUA_TTABLE);
	int numSkills = luaL_len(L, -1);
	for (int i = 1; i <= numSkills; i++)
	{
		lua_rawgeti(L, -1, i);
		lua_rawgeti(L, -1, 1);
		std::string primarySkillName = luaL_checkstring(L, -1);
		lua_rawgeti(L, -2, 2);
		std::string secondarySkillName = luaL_checkstring(L, -1);
		lua_pop(L, 3);
		skills::SkillTemplate* primarySkillTemplate = gameState->getSkillTemplate(primarySkillName);
		skills::SkillTemplate* secondarySkillTemplate = gameState->getSkillTemplate(secondarySkillName);
		shipTemplate->addSkillTemplates(primarySkillTemplate, secondarySkillTemplate);
	}

	gameState->addShipTemplate(shipTemplate);
	
	return 0;
}

int l_missile(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TTABLE);
	
	lua_getfield(L, 1, "name");
	std::string name = luaL_checkstring(L, -1);
	
	lua_getfield(L, 1, "speed");
	float speed = luaL_checknumber(L, -1);
	
	lua_getfield(L, 1, "texture");
	std::string texture = luaL_checkstring(L, -1);

	flat::util::Sprite* missileSprite = new flat::util::Sprite();
	
	missileSprite->setTexture(new flat::video::FileTexture(texture));
	
	entities::MissileTemplate* missileTemplate = new entities::MissileTemplate();
	missileTemplate->setName(name);
	missileTemplate->setSpeed(speed);
	
	missileTemplate->setSprite(missileSprite);
	
	states::GameState* gameState = (states::GameState*) lua_touserdata(L, lua_upvalueindex(1));
	gameState->addMissileTemplate(missileTemplate);
	
	return 0;
}

int l_skill(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TTABLE);
	
	lua_getfield(L, 1, "name");
	std::string name = luaL_checkstring(L, -1);
	
	lua_getfield(L, 1, "cooldown");
	float cooldown = luaL_checknumber(L, -1);
	
	lua_getfield(L, 1, "trigger");
	luaL_checktype(L, -1, LUA_TFUNCTION);
	int triggerFunctionRef = luaL_ref(L, LUA_REGISTRYINDEX);
	
	skills::SkillTemplate* skillTemplate = new skills::SkillTemplate();
	skillTemplate->setName(name);
	skillTemplate->setCooldown(cooldown);
	skillTemplate->setTriggerFunctionRef(triggerFunctionRef);
	
	states::GameState* gameState = (states::GameState*) lua_touserdata(L, lua_upvalueindex(1));
	gameState->addSkillTemplate(skillTemplate);
	
	return 0;
}

} // templates
} // lua
} // game


