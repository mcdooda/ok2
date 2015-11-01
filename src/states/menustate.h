#ifndef GAME_MENUSTATE_H
#define GAME_MENUSTATE_H

#include <flat.h>
#include <memory>

#include "../game.h"

namespace game
{
namespace states
{

class MenuState : public flat::state::State
{
	public:
		MenuState();
		MenuState(std::unique_ptr<flat::audio::Music>&& music);

		void enter(flat::state::Agent* agent) override;
		void execute(flat::state::Agent* agent) override;
		void exit(flat::state::Agent* agent) override;
		
	private:
		void update(Game* game);
		void draw(Game* game);

		void buildUi(Game* game);

		void updateUi(Game* game);

		void drawUi();
		
	private:
		std::unique_ptr<flat::audio::Music> m_music;

		std::unique_ptr<flat::sharp::ui::RootWidget> m_ui;
		flat::sharp::ui::Widget* m_logo;
		
		flat::video::Program m_program;
		flat::util::RenderSettings m_programRenderSettings;
};

} // states
} // game

#endif // GAME_MENUSTATE_H



