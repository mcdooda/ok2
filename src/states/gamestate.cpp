#include "../game.h"
#include "../entities/playerentity.h"
#include "gamestate.h"

namespace game
{
namespace states
{

void GameState::enter(flat::state::Agent* agent)
{
	Game* game = (Game*) agent;
	
	m_music = game->audio->loadMusic("rsrc/sounds/music/musique_d_ailleurs.ogg");
	m_music->play();
	
	addShip("blue", flat::geometry::Vector2(-250, 0));
	addShip("gray", flat::geometry::Vector2(-150, 0));
	addShip("green", flat::geometry::Vector2(-50, 0));
	addShip("pink", flat::geometry::Vector2(50, 0));
	addShip("red", flat::geometry::Vector2(150, 0));
	addShip("yellow", flat::geometry::Vector2(250, 0));
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
	for (std::vector<entities::Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
		(*it)->update(game, elapsedTime);
}

void GameState::draw(Game* game)
{
	game->levelPass.use();
	game->video->setClearColor(flat::video::Color::BLUE);
	game->video->clear();
	
	game->levelRenderSettings.vpMatrixUniform.setMatrix4(game->gameView.getViewProjectionMatrix());
	
	for (std::vector<entities::Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
		(*it)->draw(game->levelRenderSettings);
	
	game->renderProgram.use(game->video->window);
	game->renderProgram.draw();
}

void GameState::addShip(std::string color, flat::geometry::Vector2 position)
{
	entities::PlayerEntity* ship = new entities::PlayerEntity();
	
	entities::EntityTemplate* shipTemplate = new entities::EntityTemplate();
	shipTemplate->setSpeed(500.0f);
	
	flat::util::HeightMap* shipSprite = new flat::util::HeightMap();
	shipSprite->setPosition(position);
	shipSprite->setTexture(new flat::video::FileTexture("rsrc/images/units/ship/" + color + "/texture.png"));
	shipSprite->setHeightMap(new flat::video::FileTexture("rsrc/images/units/ship/" + color + "/heightmap.png"));
	
	ship->setTemplate(shipTemplate);
	ship->setSprite(shipSprite);
	
	ship->setRotationZ(M_PI / 2.f);
	m_entities.push_back(ship);
}

void GameState::exit(flat::state::Agent* agent)
{
	delete m_music;
}

} // states
} // game



