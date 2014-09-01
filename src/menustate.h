#ifndef GAME_MENUSTATE_H
#define GAME_MENUSTATE_H

#include <flat.h>

#include "game.h"

namespace game
{

class MenuState : public flat::state::State
{
	public:
		virtual void enter(flat::state::Agent* agent);
		virtual void execute(flat::state::Agent* agent);
		virtual void exit(flat::state::Agent* agent);
		
	private:
		void update(game::Game* game);
		void draw(game::Game* game);
		
	private:
		flat::audio::Music* m_music;
		flat::video::FileTexture* m_logoTexture;
		flat::video::Sprite* m_logoSprite;
};

}

#endif // GAME_MENUSTATE_H



