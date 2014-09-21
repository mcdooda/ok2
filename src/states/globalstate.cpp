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
	
	// frame buffer
	game->frameBuffer.setSize(game->video->window->getSize());
	const flat::video::Texture& screenTexture = game->frameBuffer.addTexture("screen");
	
	// height map pass
	game->heightMapPass.load(&game->frameBuffer, "rsrc/shaders/heightmap.frag", "rsrc/shaders/heightmap.vert");
	
	game->heightMapRenderSettings.textureUniform              = game->heightMapPass.getUniform("objectTexture");
	game->heightMapRenderSettings.bumpMapUniform              = game->heightMapPass.getUniform("objectBumpMap");
	game->heightMapRenderSettings.modelMatrixUniform          = game->heightMapPass.getUniform("modelMatrix");
	game->heightMapRenderSettings.normalMatrixUniform         = game->heightMapPass.getUniform("normalMatrix");
	game->heightMapRenderSettings.viewProjectionMatrixUniform = game->heightMapPass.getUniform("vpMatrix");
	game->heightMapRenderSettings.positionAttribute           = game->heightMapPass.getAttribute("position");
	game->heightMapRenderSettings.normalAttribute             = game->heightMapPass.getAttribute("normal");
	game->heightMapRenderSettings.uvAttribute                 = game->heightMapPass.getAttribute("uv");
	
	// sprite pass
	game->spritePass.load(&game->frameBuffer, "rsrc/shaders/sprite.frag", "rsrc/shaders/sprite.vert");
	
	game->spriteRenderSettings.textureUniform              = game->spritePass.getUniform("objectTexture");
	game->spriteRenderSettings.modelMatrixUniform          = game->spritePass.getUniform("modelMatrix");
	game->spriteRenderSettings.viewProjectionMatrixUniform = game->spritePass.getUniform("vpMatrix");
	game->spriteRenderSettings.positionAttribute           = game->spritePass.getAttribute("position");
	game->spriteRenderSettings.uvAttribute                 = game->spritePass.getAttribute("uv");
	
	// show texture pass
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



