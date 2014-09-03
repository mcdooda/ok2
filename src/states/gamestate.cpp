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
	
	entities::PlayerEntity* ship = new entities::PlayerEntity();
	
	entities::EntityTemplate* shipTemplate = new entities::EntityTemplate();
	shipTemplate->setSpeed(300.0f);
	
	flat::util::Sprite* shipSprite = new flat::util::Sprite();
	shipSprite->setTexture(new flat::video::FileTexture("rsrc/images/units/ship/blue/texture.png"));
	//shipSprite->setHeightMap(new flat::video::FileTexture("rsrc/images/units/ship/blue/heightmap.png"));
	
	ship->setTemplate(shipTemplate);
	ship->setSprite(shipSprite);
	
	ship->setRotationZ(M_PI / 2.f);
	m_entities.push_back(ship);
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

void GameState::exit(flat::state::Agent* agent)
{
	delete m_music;
}

} // states
} // game



