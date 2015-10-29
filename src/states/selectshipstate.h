#ifndef GAME_SELECTSHIPSTATE_H
#define GAME_SELECTSHIPSTATE_H

#include <flat.h>
#include <memory>

#include "../game.h"

namespace game
{
namespace states
{

class SelectShipState : public flat::state::State
{
	public:
		SelectShipState(std::unique_ptr<flat::audio::Music>&& music);
		
		virtual void enter(flat::state::Agent* agent);
		virtual void execute(flat::state::Agent* agent);
		virtual void exit(flat::state::Agent* agent);
		
	private:
		void update(Game* game);
		void draw(Game* game);
		
		void buildUi(Game* game);

		void updateUi(Game* game);
		void onShipIconClicked(flat::sharp::ui::Widget* widget, bool& eventHandled);

		void drawUi();
		
	private:
		std::unique_ptr<flat::audio::Music> m_music;
		
		std::unique_ptr<flat::sharp::ui::RootWidget> m_ui;
		std::vector<flat::sharp::ui::Widget*> m_shipIcons;
		
		flat::video::Program m_program;
		flat::util::RenderSettings m_programRenderSettings;
};

} // states
} // game

#endif // GAME_SELECTSHIPSTATE_H



