#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <flat/game.h>

namespace game
{

class Game : public flat::Game
{
	public:
		Game(const std::vector<std::string>& args);
		virtual ~Game();
		
		void openWindow();
		
	public:
		// views
		flat::video::View gameView;
		flat::video::View interfaceView;
		
		// passes
		flat::video::Pass heightMapPass;
		//flat::video::Pass spritePass;
		flat::video::Render renderProgram;
		
		// attributes & uniforms
		flat::util::RenderSettings heightMapRenderSettings;
		flat::util::RenderSettings spriteRenderSettings;
		
		flat::video::Attribute renderPositionAttribute;
		flat::video::Attribute renderUvAttribute;
};

} // game

#endif // GAME_GAME_H



