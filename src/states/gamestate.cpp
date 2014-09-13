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
	addEnemy(flat::geometry::Vector2(0, -150));
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
	game->heightMapPass.use();
	game->video->setClearColor(flat::video::Color::BLUE);
	game->video->clear();
	
	game->heightMapRenderSettings.viewProjectionMatrixUniform.setMatrix4(game->gameView.getViewProjectionMatrix());
	
	for (std::vector<entities::Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
		(*it)->draw(game->heightMapRenderSettings, game->gameView.getViewMatrix());
	
	game->renderProgram.use(game->video->window);
	game->renderProgram.draw();
}

void GameState::addShip(std::string color, flat::geometry::Vector2 position)
{
	entities::PlayerEntity* ship = new entities::PlayerEntity();
	
	entities::EntityTemplate* shipTemplate = new entities::EntityTemplate();
	shipTemplate->setSpeed(500.f);
	
	flat::util::HeightMap* shipSprite = new flat::util::HeightMap();
	shipSprite->setPosition(position);
	shipSprite->setTexture(new flat::video::FileTexture("rsrc/images/units/ships/" + color + "/texture.png"));
	shipSprite->setHeightMap(new flat::video::FileTexture("rsrc/images/units/ships/" + color + "/heightmap.png"));
	shipSprite->setBumpMap(new flat::video::FileTexture("rsrc/images/units/ships/" + color + "/bumpmap.png"));
	
	ship->setTemplate(shipTemplate);
	ship->setSprite(shipSprite);
	
	ship->setRotationZ(M_PI / 2.f);
	m_entities.push_back(ship);
}

void GameState::addEnemy(flat::geometry::Vector2 position)
{
	entities::Entity* enemy = new entities::Entity();
	
	entities::EntityTemplate* enemyTemplate = new entities::EntityTemplate();
	enemyTemplate->setSpeed(100.f);
	
	flat::util::Sprite* enemySprite = new flat::util::Sprite();
	enemySprite->setPosition(position);
	enemySprite->setTexture(new flat::video::FileTexture("rsrc/images/units/enemies/enemy1/texture.png"));
	
	enemy->setTemplate(enemyTemplate);
	enemy->setSprite(enemySprite);
	
	enemy->setRotationZ(-M_PI / 2.f);
	m_entities.push_back(enemy);
}

void GameState::exit(flat::state::Agent* agent)
{
	delete m_music;
}

} // states
} // game



