#include <iostream>
#include "../game.h"
#include "../entities/playership.h"
#include "../entities/lua/entity.h"
#include "../timers/lua/timer.h"
#include "../lua/templates.h"
#include "../lua/pop.h"
#include "gamestate.h"

namespace game
{
namespace states
{

void GameState::enter(flat::state::Agent* agent)
{
	Game* game = (Game*) agent;
	
	initMusic(game);
	
	loadLuaLibraries(game);
	loadTemplates(game);
	
	lua_State* L = game->luaState;
	float time = game->time->getTime();
	
	entities::Ship* ship = addShip("blue", flat::geometry::Vector2(-250, 0), M_PI / 2, new entities::PlayerShip());
	entities::lua::initEntity(L, ship, time);
	
	ship = addShip("gray", flat::geometry::Vector2(-150, 0), M_PI / 2, new entities::PlayerShip());
	entities::lua::initEntity(L, ship, time);
	
	ship = addShip("green", flat::geometry::Vector2(-50, 0), M_PI / 2, new entities::PlayerShip());
	entities::lua::initEntity(L, ship, time);
	
	ship = addShip("pink", flat::geometry::Vector2(50, 0), M_PI / 2, new entities::PlayerShip());
	entities::lua::initEntity(L, ship, time);
	
	ship = addShip("red", flat::geometry::Vector2(150, 0), M_PI / 2, new entities::PlayerShip());
	entities::lua::initEntity(L, ship, time);
	
	ship = addShip("yellow", flat::geometry::Vector2(250, 0), M_PI / 2, new entities::PlayerShip());
	entities::lua::initEntity(L, ship, time);
}

void GameState::initMusic(Game* game)
{
	m_music = game->audio->loadMusic("rsrc/sounds/music/musique_d_ailleurs.ogg");
	m_music->play();
}

void GameState::loadLuaLibraries(Game* game)
{
	lua_State* L = game->luaState;
	entities::lua::open(L);
	timers::lua::open(L, this, game);
	lua::templates::open(L, this, game);
	lua::pop::open(L, this, game);
}

void GameState::loadTemplates(Game* game)
{
	flat::lua::doFile(game->luaState, "rsrc/lua/templates.lua");
}

void GameState::addShipTemplate(entities::ShipTemplate* shipTemplate)
{
	m_shipTemplates[shipTemplate->getName()] = shipTemplate;
}

void GameState::addMissileTemplate(entities::MissileTemplate* missileTemplate)
{
	m_missileTemplates[missileTemplate->getName()] = missileTemplate;
}

void GameState::addSkillTemplate(skills::SkillTemplate* skillTemplate)
{
	m_skillTemplates[skillTemplate->getName()] = skillTemplate;
}

skills::SkillTemplate* GameState::getSkillTemplate(const std::string& skillName)
{
	return m_skillTemplates[skillName];
}

entities::Ship* GameState::addShip(const std::string& name, const flat::geometry::Vector2& position, float rotationZ, entities::Ship* existingShip)
{
	entities::Ship* ship;
	
	if (existingShip != NULL)
		ship = existingShip;
		
	else
		ship = new entities::Ship();
	
	entities::ShipTemplate* shipTemplate = m_shipTemplates[name];
	
	if (shipTemplate == NULL)
	{
		std::cerr << name << " ship does not exist" << std::endl;
		::exit(1);
	}
	
	ship->setTemplate(shipTemplate);
	
	ship->setPosition(position);
	ship->setRotationZ(rotationZ);
	m_ships.push_back(ship);
	
	return ship;
}

entities::Missile* GameState::addMissile(const std::string& name, const flat::geometry::Vector2& position, float rotationZ)
{
	entities::Missile* missile = new entities::Missile();
	
	entities::MissileTemplate* missileTemplate = m_missileTemplates[name];
	
	if (missileTemplate == NULL)
	{
		std::cerr << name << " missile does not exist" << std::endl;
		::exit(1);
	}
	
	missile->setTemplate(missileTemplate);
	
	missile->setPosition(position);
	missile->setRotationZ(rotationZ);
	m_missiles.push_back(missile);
	
	return missile;
}

void GameState::addTimer(timers::Timer* timer)
{
	m_timers.insert(timer);
}

void GameState::execute(flat::state::Agent* agent)
{
	Game* game = (Game*) agent;
	update(game);
	draw(game);
}

void GameState::update(Game* game)
{
	float time = game->time->getTime();
	float elapsedTime = game->time->getFrameTime();
	lua_State* L = game->luaState;
	
	// creates a copy in order to allow skills to create new ships
	std::vector<entities::Ship*> ships = m_ships;
	std::vector<entities::Missile*> missiles = m_missiles;
	
	for (std::vector<entities::Ship*>::iterator it = ships.begin(); it != ships.end(); it++)
	{
		(*it)->update(game, elapsedTime);
		entities::lua::triggerEntityUpdateFunction(L, *it, time, elapsedTime);
	}
		
	for (std::vector<entities::Missile*>::iterator it = missiles.begin(); it != missiles.end(); it++)
	{
		(*it)->update(game, elapsedTime);
		entities::lua::triggerEntityUpdateFunction(L, *it, time, elapsedTime);
	}
	
	updateTimers(game);
}

void GameState::draw(Game* game)
{
	// sprites
	game->spritePass.use();
	
	game->video->setClearColor(flat::video::Color::BLUE);
	game->video->clear();
	
	game->spriteRenderSettings.viewProjectionMatrixUniform.setMatrix4(game->gameView.getViewProjectionMatrix());
	
	for (std::vector<entities::Missile*>::iterator it = m_missiles.begin(); it != m_missiles.end(); it++)
		(*it)->draw(game->spriteRenderSettings, game->gameView.getViewMatrix());
		
	// heightmaps
	game->heightMapPass.use();
	
	game->heightMapRenderSettings.viewProjectionMatrixUniform.setMatrix4(game->gameView.getViewProjectionMatrix());
	
	for (std::vector<entities::Ship*>::iterator it = m_ships.begin(); it != m_ships.end(); it++)
		(*it)->draw(game->heightMapRenderSettings, game->gameView.getViewMatrix());
	
	// final texture
	game->renderProgram.use(game->video->window);
	game->renderProgram.draw();
}

void GameState::updateTimers(Game* game)
{
	lua_State* L = game->luaState;
	float time = game->time->getTime();
	
	std::set<timers::Timer*> stoppedTimers;
	
	for (std::set<timers::Timer*>::iterator it = m_timers.begin(); it != m_timers.end(); it++)
	{
		timers::Timer* timer = *it;
		timer->updateTime(time);
		timers::lua::triggerTimerUpdateFunction(L, timer);
		if (timer->isStopped() || timer->isFinished())
			stoppedTimers.insert(timer);
	}
	
	for (std::set<timers::Timer*>::iterator it = stoppedTimers.begin(); it != stoppedTimers.end(); it++)
	{
		timers::Timer* timer = *it;
		m_timers.erase(timer);
		timers::lua::triggerTimerEndFunction(L, timer);
		timers::lua::destroyTimerState(L, timer);
		delete timer;
	}
}

void GameState::exit(flat::state::Agent* agent)
{
	delete m_music;
}

} // states
} // game



