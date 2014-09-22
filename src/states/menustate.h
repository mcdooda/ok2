#ifndef GAME_MENUSTATE_H
#define GAME_MENUSTATE_H

#include <flat.h>

#include "../game.h"

namespace game
{
namespace states
{

class MenuState : public flat::state::State
{
	public:
		virtual void enter(flat::state::Agent* agent);
		virtual void execute(flat::state::Agent* agent);
		virtual void exit(flat::state::Agent* agent);
		
	private:
		void update(Game* game);
		void draw(Game* game);
		
	private:
		flat::audio::Music* m_music;
		flat::video::FileTexture* m_logoTexture;
		flat::util::Sprite* m_logoSprite;
		
		flat::video::Program m_program;
		flat::util::RenderSettings m_programRenderSettings;
};

} // states
} // game

#endif // GAME_MENUSTATE_H



