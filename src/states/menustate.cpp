#include "../game.h"
#include "menustate.h"
#include "gamestate.h"

namespace game
{
namespace states
{

void MenuState::enter(flat::state::Agent* agent)
{
	Game* game = (Game*) agent;
	
	m_music = game->audio->loadMusic("rsrc/sounds/music/a_war_without_weapons.ogg");
	m_music->play();
	
	m_logoTexture = new flat::video::FileTexture("rsrc/images/logo.png");
	m_logoSprite = new flat::util::Sprite();
	m_logoSprite->setTexture(m_logoTexture);
}

void MenuState::execute(flat::state::Agent* agent)
{
	Game* game = (Game*) agent;
	update(game);
	draw(game);
	
	if (game->input->keyboard->isJustPressed(K(SPACE)))
		game->getStateMachine()->setState(new GameState());
}

void MenuState::exit(flat::state::Agent* agent)
{
	delete m_music;
	delete m_logoTexture;
	delete m_logoSprite;
}

void MenuState::update(Game* game)
{
	m_logoSprite->setPosition(flat::geometry::Vector2(0, sin(game->time->getTime() * 1.5f) * 10.f));
}

void MenuState::draw(Game* game)
{
	game->spritePass.use();
	game->video->setClearColor(flat::video::Color::BLUE);
	game->video->clear();
	
	game->spriteRenderSettings.viewProjectionMatrixUniform.setMatrix4(game->gameView.getViewProjectionMatrix());
	
	m_logoSprite->draw(game->spriteRenderSettings, game->gameView.getViewMatrix());
	
	game->renderProgram.use(game->video->window);
	game->renderProgram.draw();
}

} // states
} // game



