#include <iostream>
#include "templates.h"
#include "../entities/shiptemplate.h"

namespace game
{
namespace lua
{
namespace templates
{

void open(lua_State* L, states::GameState* gameState, Game* game)
{
	const luaL_Reg funcs[] = {
		{"ship",    l_ship},
		{"missile", l_missile},
		{"skill",   l_skill},
		{nullptr, nullptr}
	};
	registerGameStateClosures(L, game, gameState, funcs);
}
	
int l_ship(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TTABLE);
	
	lua_getfield(L, 1, "name");
	std::string name = luaL_checkstring(L, -1);
	
	lua_getfield(L, 1, "speed");
	float speed = luaL_checknumber(L, -1);
	
	lua_getfield(L, 1, "health");
	int health = luaL_checkint(L, -1);
	
	lua_getfield(L, 1, "experience");
	unsigned int experience = luaL_optint(L, -1, 0);
	
	lua_getfield(L, 1, "texture");
	std::string texture = luaL_checkstring(L, -1);
	
	lua_getfield(L, 1, "heightmap");
	std::string heightMapFileName;
	if (!lua_isnil(L, -1))
	{
		heightMapFileName = luaL_checkstring(L, -1);
	}
	
	lua_getfield(L, 1, "bumpmap");
	std::string bumpMapFileName;
	if (!lua_isnil(L, -1))
	{
		bumpMapFileName = luaL_checkstring(L, -1);
	}
	
	lua_getfield(L, 1, "pop");
	int popFunctionRef = LUA_NOREF;
	if (lua_type(L, -1) == LUA_TFUNCTION)
		popFunctionRef = luaL_ref(L, LUA_REGISTRYINDEX);
	
	lua_getfield(L, 1, "update");
	int updateFunctionRef = LUA_NOREF;
	if (lua_type(L, -1) == LUA_TFUNCTION)
		updateFunctionRef = luaL_ref(L, LUA_REGISTRYINDEX);
	
	entities::ShipTemplate* shipTemplate = new entities::ShipTemplate();
	shipTemplate->setName(name);
	shipTemplate->setSpeed(speed);
	shipTemplate->setHealth(health);
	shipTemplate->setExperienceValue(experience);
	shipTemplate->setPopFunctionRef(popFunctionRef);
	shipTemplate->setUpdateFunctionRef(updateFunctionRef);
	
	flat::util::Sprite* shipSprite;
	
	if (heightMapFileName != "")
		shipSprite = new flat::util::HeightMap();
		
	else
		shipSprite = new flat::util::Sprite();
	
	Game* game = getGame(L);
	
	shipSprite->setTexture(game->video->getTexture(texture));
	
	if (heightMapFileName != "")
	{
		flat::util::HeightMap* shipHeightMap = static_cast<flat::util::HeightMap*>(shipSprite);
		
		shipHeightMap->setHeightMap(game->video->getTexture(heightMapFileName));
		
		if (bumpMapFileName != "")
			shipHeightMap->setBumpMap(game->video->getTexture(bumpMapFileName));
	}
	
	shipTemplate->setSprite(shipSprite);
	
	states::GameState* gameState = getGameState(L);
	
	lua_getfield(L, 1, "levels");
	if (!lua_isnil(L, -1))
	{
		luaL_checktype(L, -1, LUA_TTABLE);
		int numSkills = luaL_len(L, -1);
		for (int i = 1; i <= numSkills; i++)
		{
			lua_rawgeti(L, -1, i);
			
			lua_rawgeti(L, -1, 1);
			unsigned int levelExperience = luaL_checkint(L, -1);
		
			lua_rawgeti(L, -2, 2);
			skills::SkillTemplate* primarySkillTemplate = nullptr;
			if (!lua_isnil(L, -1))
			{
				std::string primarySkillName = luaL_checkstring(L, -1);
				primarySkillTemplate = gameState->getSkillTemplate(primarySkillName);
			}
		
			lua_rawgeti(L, -3, 3);
			skills::SkillTemplate* secondarySkillTemplate = nullptr;
			if (!lua_isnil(L, -1))
			{
				std::string secondarySkillName = luaL_checkstring(L, -1);
				secondarySkillTemplate = gameState->getSkillTemplate(secondarySkillName);
			}
		
			shipTemplate->addLevel(levelExperience, primarySkillTemplate, secondarySkillTemplate);
		
			lua_pop(L, 4);
		}
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
	
	lua_getfield(L, 1, "damage");
	int damage = luaL_checkint(L, -1);
	
	lua_getfield(L, 1, "texture");
	std::string textureFileName = luaL_checkstring(L, -1);
	
	lua_getfield(L, 1, "pop");
	int popFunctionRef = LUA_NOREF;
	if (lua_type(L, -1) == LUA_TFUNCTION)
		popFunctionRef = luaL_ref(L, LUA_REGISTRYINDEX);
	
	lua_getfield(L, 1, "update");
	int updateFunctionRef = LUA_NOREF;
	if (lua_type(L, -1) == LUA_TFUNCTION)
		updateFunctionRef = luaL_ref(L, LUA_REGISTRYINDEX);

	flat::util::Sprite* missileSprite = new flat::util::Sprite();
	
	Game* game = getGame(L);
	missileSprite->setTexture(game->video->getTexture(textureFileName));
	
	entities::MissileTemplate* missileTemplate = new entities::MissileTemplate();
	missileTemplate->setName(name);
	missileTemplate->setSpeed(speed);
	missileTemplate->setDamage(damage);
	missileTemplate->setPopFunctionRef(popFunctionRef);
	missileTemplate->setUpdateFunctionRef(updateFunctionRef);
	
	missileTemplate->setSprite(missileSprite);
	
	states::GameState* gameState = getGameState(L);
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
	
	states::GameState* gameState = getGameState(L);
	gameState->addSkillTemplate(skillTemplate);
	
	return 0;
}

} // templates
} // lua
} // game



