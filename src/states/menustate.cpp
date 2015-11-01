#include "../game.h"
#include "menustate.h"
#include "selectshipstate.h"

namespace game
{
namespace states
{

MenuState::MenuState()
{

}

MenuState::MenuState(std::unique_ptr<flat::audio::Music>&& music) :
	m_music(std::move(music))
{

}

void MenuState::enter(flat::state::Agent* agent)
{
	Game* game = agent->to<Game>();
	
	if (!m_music.get())
	{
		m_music.reset(game->audio->loadMusic("rsrc/sounds/music/a_war_without_weapons.ogg"));
		m_music->play();
	}
	
	buildUi(game);
	
	m_program.load("rsrc/shaders/ui.frag", "rsrc/shaders/ui.vert");
	
	m_programRenderSettings.textureUniform              = m_program.getUniform("objectTexture");
	m_programRenderSettings.colorUniform                = m_program.getUniform("color");
	m_programRenderSettings.modelMatrixUniform          = m_program.getUniform("modelMatrix");
	m_programRenderSettings.viewProjectionMatrixUniform = m_program.getUniform("vpMatrix");
	m_programRenderSettings.positionAttribute           = m_program.getAttribute("position");
	m_programRenderSettings.uvAttribute                 = m_program.getAttribute("uv");
}

void MenuState::execute(flat::state::Agent* agent)
{
	Game* game = agent->to<Game>();
	update(game);
	draw(game);

	if (game->input->keyboard->isJustPressed(K(SPACE)))
			game->getStateMachine()->setNewStateMove<SelectShipState>(std::move(m_music));
}

void MenuState::exit(flat::state::Agent* agent)
{

}

void MenuState::update(Game* game)
{
	if (game->input->keyboard->isJustPressed(K(ESCAPE)))
		game->stop();

	updateUi(game);
}

void MenuState::draw(Game* game)
{
	m_program.use(game->video->window);
	
	game->video->setClearColor(flat::video::Color::BLUE);
	game->video->clear();
	
	m_programRenderSettings.viewProjectionMatrixUniform.setMatrix4(game->interfaceView.getViewProjectionMatrix());
	
	drawUi();
}

void MenuState::buildUi(Game* game)
{
	flat::sharp::ui::WidgetFactory widgetFactory(*game);

	flat::sharp::ui::RootWidget* ui = widgetFactory.makeRoot();

	m_logo = widgetFactory.makeImage("rsrc/images/logo.png");
	m_logo->setPositionPolicy(flat::sharp::ui::Widget::PositionPolicy::CENTER);
	ui->addChild(m_logo);

	ui->fullLayout();

	m_ui.reset(ui);
}

void MenuState::updateUi(Game* game)
{
	flat::sharp::ui::RootWidget* ui = m_ui.get();

	m_logo->setPosition(flat::geometry::Vector2(0, sin(game->time->getTime() * 1.5f) * 10.f));

	if (game->input->window->isResized())
		ui->fullLayout();

	ui->updateInput();
}

void MenuState::drawUi()
{
	m_ui->draw(m_programRenderSettings);
}

} // states
} // game



