#include <iostream>
#include "../game.h"
#include "../entities/playership.h"
#include "../entities/lua/entity.h"
#include "../arena/lua/arena.h"
#include "../timers/lua/timer.h"
#include "../lua/templates.h"
#include "../lua/pop.h"
#include "../lua/level.h"
#include "../lua/time.h"
#include "gamestate.h"

namespace game
{
namespace states
{

void GameState::enter(flat::state::Agent* agent)
{
	Game* game = (Game*) agent;
	
	static const float arenaWidth = 600;
	static const float arenaHeight = 1080;
	flat::geometry::Vector2 arenaSize = flat::geometry::Vector2(arenaWidth, arenaHeight);
	m_arena = new arena::Arena(arenaSize, 100);
	
	initMusic(game);
	initGraphics(game);
	
	loadLuaLibraries(game);
	loadShip(game, "blue");
	loadLevel(game);
}

void GameState::initMusic(Game* game)
{
	m_music = game->audio->loadMusic("rsrc/sounds/music/musique_d_ailleurs.ogg");
	m_music->play();
}

void GameState::initGraphics(Game* game)
{
	m_view.reset();
	m_view.updateProjection(m_arena->getSize());
	
	// frame buffer
	m_frameBuffer.setSize(m_arena->getSize() * (game->video->window->getDesktopSize().getY() / m_arena->getSize().getY()));
	const flat::video::Texture& screenTexture = m_frameBuffer.addTexture("screen");
	
	// height map pass
	m_heightMapPass.load(&m_frameBuffer, "rsrc/shaders/heightmap.frag", "rsrc/shaders/heightmap.vert");
	
	m_heightMapRenderSettings.textureUniform              = m_heightMapPass.getUniform("objectTexture");
	m_heightMapRenderSettings.bumpMapUniform              = m_heightMapPass.getUniform("objectBumpMap");
	m_heightMapRenderSettings.modelMatrixUniform          = m_heightMapPass.getUniform("modelMatrix");
	m_heightMapRenderSettings.normalMatrixUniform         = m_heightMapPass.getUniform("normalMatrix");
	m_heightMapRenderSettings.viewProjectionMatrixUniform = m_heightMapPass.getUniform("vpMatrix");
	m_heightMapRenderSettings.positionAttribute           = m_heightMapPass.getAttribute("position");
	m_heightMapRenderSettings.normalAttribute             = m_heightMapPass.getAttribute("normal");
	m_heightMapRenderSettings.uvAttribute                 = m_heightMapPass.getAttribute("uv");
	
	// sprite pass
	m_spritePass.load(&m_frameBuffer, "rsrc/shaders/sprite.frag", "rsrc/shaders/sprite.vert");
	
	m_spriteRenderSettings.textureUniform              = m_spritePass.getUniform("objectTexture");
	m_spriteRenderSettings.modelMatrixUniform          = m_spritePass.getUniform("modelMatrix");
	m_spriteRenderSettings.viewProjectionMatrixUniform = m_spritePass.getUniform("vpMatrix");
	m_spriteRenderSettings.positionAttribute           = m_spritePass.getAttribute("position");
	m_spriteRenderSettings.uvAttribute                 = m_spritePass.getAttribute("uv");
	
	// show texture pass
	m_renderProgram.load("rsrc/shaders/renderprogram.frag", "rsrc/shaders/renderprogram.vert");
	m_renderProgram.addInputTexture(screenTexture);
	
	m_arenaSizeUniform = m_renderProgram.getUniform("arenaSize");
	m_screenSizeUniform = m_renderProgram.getUniform("screenSize");
}

void GameState::loadLuaLibraries(Game* game)
{
	lua_State* L = game->luaState;
	entities::lua::open(L);
	arena::lua::open(L, m_arena);
	timers::lua::open(L, this, game);
	lua::templates::open(L, this, game);
	lua::pop::open(L, this, game);
	lua::time::open(L, game);
	flat::lua::loadLib(game->luaState, "rsrc/lua/load.lua", "load");
}

void GameState::loadShip(Game* game, std::string shipName)
{
	flat::lua::doFile(game->luaState, "rsrc/lua/ships/" + shipName + "/setup.lua");
}

void GameState::loadLevel(Game* game)
{
	m_levelCoroutineRef = lua::level::load(game->luaState, "rsrc/lua/levels/level1.lua");
}

void GameState::updateLevel(Game* game)
{
	lua_State* L = game->luaState;
	bool levelFinished = lua::level::resume(L, m_levelCoroutineRef);
	if (levelFinished)
	{
		lua::level::destroyState(L, m_levelCoroutineRef);
		m_levelCoroutineRef = LUA_NOREF;
	}
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

entities::Ship* GameState::addShip(const std::string& name, const flat::geometry::Vector2& position, float rotationZ, entities::Entity::Side side, entities::Ship* existingShip)
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
	ship->setSide(side);
	m_arena->addShip(ship);
	
	return ship;
}

entities::Missile* GameState::addMissile(const std::string& name, const flat::geometry::Vector2& position, float rotationZ, entities::Entity::Side side)
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
	missile->setSide(side);
	m_arena->addMissile(missile);
	
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
	
	updateLevel(game);
	
	for (int i = entities::Entity::ALLY; i < entities::Entity::NUM_SIDES; i++)
	{
		entities::Entity::Side side = (entities::Entity::Side) i;
		
		// creates a copy before iterating
		std::set<entities::Ship*> ships(m_arena->getShips(side));
	
		for (std::set<entities::Ship*>::iterator it = ships.begin(); it != ships.end(); it++)
		{
			(*it)->update(game, elapsedTime, m_arena);
			entities::lua::triggerEntityUpdateFunction(L, *it, time, elapsedTime);
		}
	
		// creates a copy before iterating
		std::set<entities::Missile*> missiles(m_arena->getMissiles(side));
		
		for (std::set<entities::Missile*>::iterator it = missiles.begin(); it != missiles.end(); it++)
		{
			(*it)->update(game, elapsedTime, m_arena);
			entities::lua::triggerEntityUpdateFunction(L, *it, time, elapsedTime);
		}
	}
	
	updateTimers(game);
}

void GameState::draw(Game* game)
{
	// sprites
	m_spritePass.use();
	
	game->video->setClearColor(flat::video::Color::BLUE);
	game->video->clear();
	
	m_spriteRenderSettings.viewProjectionMatrixUniform.setMatrix4(m_view.getViewProjectionMatrix());
	
	for (int i = entities::Entity::ALLY; i < entities::Entity::NUM_SIDES; i++)
	{
		entities::Entity::Side side = (entities::Entity::Side) i;
		
		const std::set<entities::Missile*>& missiles = m_arena->getMissiles(side);
	
		for (std::set<entities::Missile*>::iterator it = missiles.begin(); it != missiles.end(); it++)
			(*it)->draw(m_spriteRenderSettings, m_view.getViewMatrix());
	}
		
	// heightmaps
	m_heightMapPass.use();
	
	m_heightMapRenderSettings.viewProjectionMatrixUniform.setMatrix4(m_view.getViewProjectionMatrix());
	
	for (int i = entities::Entity::ALLY; i < entities::Entity::NUM_SIDES; i++)
	{
		entities::Entity::Side side = (entities::Entity::Side) i;
		
		const std::set<entities::Ship*>& ships = m_arena->getShips(side);
	
		for (std::set<entities::Ship*>::iterator it = ships.begin(); it != ships.end(); it++)
			(*it)->draw(m_heightMapRenderSettings, m_view.getViewMatrix());
	}
	
	// final texture
	m_renderProgram.use(game->video->window);
	
	m_screenSizeUniform.setVector2(game->video->window->getSize());
	m_arenaSizeUniform.setVector2(m_arena->getSize());
	
	game->video->setClearColor(flat::video::Color::BLACK);
	game->video->clear();
	
	m_renderProgram.draw();
}

void GameState::updateTimers(Game* game)
{
	lua_State* L = game->luaState;
	float time = game->time->getTime();
	
	std::set<timers::Timer*> stoppedTimers;
	std::set<timers::Timer*> timers = m_timers; // allows timers to add new timers!
	
	for (std::set<timers::Timer*>::iterator it = timers.begin(); it != timers.end(); it++)
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
	delete m_arena;
	delete m_music;
}

} // states
} // game



