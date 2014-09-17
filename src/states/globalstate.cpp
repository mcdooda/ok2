#include <iostream>
#include "../game.h"
#include "globalstate.h"

namespace game
{
namespace states
{

void GlobalState::enter(flat::state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	game->video->window->setTitle("Ocean's Keeper 2");
	
	game->heightMapPass.load(game->video->window->getSize(), "rsrc/shaders/heightmap.frag", "rsrc/shaders/heightmap.vert");
	const flat::video::Texture& screenTexture = game->heightMapPass.addOutputTexture("screen");
	
	game->heightMapRenderSettings.textureUniform              = game->heightMapPass.getUniform("objectTexture");
	game->heightMapRenderSettings.bumpMapUniform              = game->heightMapPass.getUniform("objectBumpMap");
	game->heightMapRenderSettings.modelMatrixUniform          = game->heightMapPass.getUniform("modelMatrix");
	game->heightMapRenderSettings.normalMatrixUniform         = game->heightMapPass.getUniform("normalMatrix");
	game->heightMapRenderSettings.viewProjectionMatrixUniform = game->heightMapPass.getUniform("vpMatrix");
	game->heightMapRenderSettings.positionAttribute           = game->heightMapPass.getAttribute("position");
	game->heightMapRenderSettings.normalAttribute             = game->heightMapPass.getAttribute("normal");
	game->heightMapRenderSettings.uvAttribute                 = game->heightMapPass.getAttribute("uv");
	
	game->renderProgram.load("rsrc/shaders/renderprogram.frag", "rsrc/shaders/renderprogram.vert");
	game->renderProgram.addInputTexture(screenTexture);
	
	game->renderPositionAttribute = game->renderProgram.getAttribute("position");
	game->renderUvAttribute = game->renderProgram.getAttribute("uv");
	
	resetViews(game);
	
	game->luaState = flat::lua::open();
}

void GlobalState::execute(flat::state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	
	if (game->input->keyboard->isJustPressed(K(ESCAPE)))
		game->stop();
		
	if (game->input->keyboard->isJustPressed(K(P)))
		game->time->togglePause();
		
	if (game->input->window->isResized())
		resetViews(game);
}

void GlobalState::exit(flat::state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	
	flat::lua::close(game->luaState);
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

} // states
} // game



