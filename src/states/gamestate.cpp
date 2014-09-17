#include <iostream>
#include "../game.h"
#include "../entities/playership.h"
#include "../lua/templates.h"
#include "gamestate.h"

namespace game
{
namespace states
{

void GameState::enter(flat::state::Agent* agent)
{
	Game* game = (Game*) agent;
	
	initMusic(game);
	
	loadTemplates(game);
	
	addShip("blue", flat::geometry::Vector2(-250, 0));
	addShip("gray", flat::geometry::Vector2(-150, 0));
	addShip("green", flat::geometry::Vector2(-50, 0));
	addShip("pink", flat::geometry::Vector2(50, 0));
	addShip("red", flat::geometry::Vector2(150, 0));
	addShip("yellow", flat::geometry::Vector2(250, 0));
}

void GameState::initMusic(Game* game)
{
	m_music = game->audio->loadMusic("rsrc/sounds/music/musique_d_ailleurs.ogg");
	m_music->play();
}

void GameState::loadTemplates(Game* game)
{
	lua::templates::open(game->luaState, this);
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

void GameState::execute(flat::state::Agent* agent)
{
	Game* game = (Game*) agent;
	update(game);
	draw(game);
}

void GameState::update(Game* game)
{
	float elapsedTime = game->time->getFrameTime();
	for (std::vector<entities::Entity*>::iterator it = m_ships.begin(); it != m_ships.end(); it++)
		(*it)->update(game, elapsedTime);
}

void GameState::draw(Game* game)
{
	game->heightMapPass.use();
	game->video->setClearColor(flat::video::Color::BLUE);
	game->video->clear();
	
	game->heightMapRenderSettings.viewProjectionMatrixUniform.setMatrix4(game->gameView.getViewProjectionMatrix());
	
	for (std::vector<entities::Entity*>::iterator it = m_ships.begin(); it != m_ships.end(); it++)
		(*it)->draw(game->heightMapRenderSettings, game->gameView.getViewMatrix());
	
	game->renderProgram.use(game->video->window);
	game->renderProgram.draw();
}

void GameState::addShip(const std::string& name, const flat::geometry::Vector2& position)
{
	entities::PlayerShip* ship = new entities::PlayerShip();
	
	entities::EntityTemplate* shipTemplate = m_shipTemplates[name];
	
	if (shipTemplate == NULL)
	{
		std::cerr << name << " ship does not exist" << std::endl;
		::exit(1);
	}
	
	ship->setTemplate(shipTemplate);
	
	ship->setPosition(position);
	ship->setRotationZ(M_PI / 2.f);
	m_ships.push_back(ship);
}

void GameState::exit(flat::state::Agent* agent)
{
	delete m_music;
}

} // states
} // game



