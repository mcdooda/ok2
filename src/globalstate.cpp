#include "globalstate.h"
#include "game.h"

namespace game
{

void GlobalState::enter(flat::state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	game->video->window->setTitle("Ocean's Keeper 2");
	
	game->levelPass.load(game->video->window->getSize(), "rsrc/shaders/levelpass.frag", "rsrc/shaders/levelpass.vert");
	const flat::video::Texture& screenTexture = game->levelPass.addOutputTexture("screen");
	
	game->renderProgram.load("rsrc/shaders/renderprogram.frag", "rsrc/shaders/renderprogram.vert");
	game->renderProgram.addInputTexture(screenTexture);
	
	game->levelPositionAttribute = game->levelPass.getAttribute("position");
	game->levelUvAttribute = game->levelPass.getAttribute("uv");
	game->levelVpMatrixUniform = game->levelPass.getUniform("vpMatrix");
	game->levelTextureUniform = game->levelPass.getUniform("objectTexture");
	
	game->renderPositionAttribute = game->renderProgram.getAttribute("position");
	game->renderUvAttribute = game->renderProgram.getAttribute("uv");
	
	resetViews(game);
}

void GlobalState::execute(flat::state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	
	if (game->input->keyboard->isJustPressed(K(ESCAPE)))
		game->stop();
		
	if (game->input->window->isResized())
		resetViews(game);
}

void GlobalState::exit(flat::state::Agent* agent)
{
	
}

void GlobalState::resetViews(game::Game* game)
{
	const flat::geometry::Vector2 windowSize = game->video->window->getSize();
	
	game->gameView.reset();
	game->gameView.updateProjection(windowSize);
	
	game->interfaceView.reset();
	game->interfaceView.move(windowSize / -2.0f);
	game->interfaceView.updateProjection(windowSize);
}

} // game



