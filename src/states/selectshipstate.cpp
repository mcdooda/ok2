#include "../game.h"
#include "selectshipstate.h"
#include "gamestate.h"

namespace game
{
namespace states
{

SelectShipState::SelectShipState(std::unique_ptr<flat::audio::Music>&& music)
	: m_music(std::move(music))
{
	
}

void SelectShipState::enter(flat::state::Agent* agent)
{
	//Game* game = static_cast<Game*>(agent);
	
	m_program.load("rsrc/shaders/sprite.frag", "rsrc/shaders/sprite.vert");
	
	m_programRenderSettings.textureUniform              = m_program.getUniform("objectTexture");
	m_programRenderSettings.colorUniform                = m_program.getUniform("color");
	m_programRenderSettings.modelMatrixUniform          = m_program.getUniform("modelMatrix");
	m_programRenderSettings.viewProjectionMatrixUniform = m_program.getUniform("vpMatrix");
	m_programRenderSettings.positionAttribute           = m_program.getAttribute("position");
	m_programRenderSettings.uvAttribute                 = m_program.getAttribute("uv");
}

void SelectShipState::execute(flat::state::Agent* agent)
{
	Game* game = static_cast<Game*>(agent);
	update(game);
	draw(game);
	
	if (game->input->keyboard->isJustPressed(K(SPACE)))
		game->getStateMachine()->setState(new GameState());
}

void SelectShipState::exit(flat::state::Agent* agent)
{
	
}

void SelectShipState::update(Game* game)
{
	const flat::geometry::Vector2& windowSize = game->video->window->getSize();
	(void)windowSize;
}

void SelectShipState::draw(Game* game)
{
	m_program.use(game->video->window);
	
	game->video->setClearColor(flat::video::Color::BLUE);
	game->video->clear();
	
	m_programRenderSettings.viewProjectionMatrixUniform.setMatrix4(game->interfaceView.getViewProjectionMatrix());
}

} // states
} // game



