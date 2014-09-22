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
	
	m_program.load("rsrc/shaders/sprite.frag", "rsrc/shaders/sprite.vert");
	
	m_programRenderSettings.textureUniform              = m_program.getUniform("objectTexture");
	m_programRenderSettings.modelMatrixUniform          = m_program.getUniform("modelMatrix");
	m_programRenderSettings.viewProjectionMatrixUniform = m_program.getUniform("vpMatrix");
	m_programRenderSettings.positionAttribute           = m_program.getAttribute("position");
	m_programRenderSettings.uvAttribute                 = m_program.getAttribute("uv");
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
	const flat::geometry::Vector2& windowSize = game->video->window->getSize();
	m_logoSprite->setPosition(windowSize / 2.f + flat::geometry::Vector2(0, sin(game->time->getTime() * 1.5f) * 10.f));
}

void MenuState::draw(Game* game)
{
	m_program.use(game->video->window);
	
	game->video->setClearColor(flat::video::Color::BLUE);
	game->video->clear();
	
	m_programRenderSettings.viewProjectionMatrixUniform.setMatrix4(game->interfaceView.getViewProjectionMatrix());
	
	m_logoSprite->draw(m_programRenderSettings, game->interfaceView.getViewMatrix());
}

} // states
} // game



