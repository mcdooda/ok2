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
	Game* game = agent->to<Game>();
	game->video->window->showCursor();
	
	buildUi(game);
	
	m_program.load("rsrc/shaders/ui.frag", "rsrc/shaders/ui.vert");
	
	m_programRenderSettings.textureUniform              = m_program.getUniform("objectTexture");
	m_programRenderSettings.colorUniform                = m_program.getUniform("color");
	m_programRenderSettings.modelMatrixUniform          = m_program.getUniform("modelMatrix");
	m_programRenderSettings.viewProjectionMatrixUniform = m_program.getUniform("vpMatrix");
	m_programRenderSettings.positionAttribute           = m_program.getAttribute("position");
	m_programRenderSettings.uvAttribute                 = m_program.getAttribute("uv");
}

void SelectShipState::execute(flat::state::Agent* agent)
{
	Game* game = agent->to<Game>();
	update(game);
	draw(game);
	
	if (game->input->keyboard->isJustPressed(K(SPACE)))
		game->getStateMachine()->setState(new GameState());
}

void SelectShipState::exit(flat::state::Agent* agent)
{
	Game* game = agent->to<Game>();
	game->video->window->hideCursor();
}

void SelectShipState::update(Game* game)
{
	updateUi(game);
}

void SelectShipState::draw(Game* game)
{
	m_program.use(game->video->window);
	
	game->video->setClearColor(flat::video::Color::BLUE);
	game->video->clear();
	
	m_programRenderSettings.viewProjectionMatrixUniform.setMatrix4(game->interfaceView.getViewProjectionMatrix());
	
	drawUi();
}

void SelectShipState::buildUi(Game* game)
{
	flat::sharp::ui::WidgetFactory widgetFactory(*game);
	
	flat::sharp::ui::RootWidget* ui = widgetFactory.makeRoot();

	{
		flat::sharp::ui::Widget* shipsContainer = widgetFactory.makeLineFlow();

		std::shared_ptr<const flat::video::FileTexture> texture = game->video->getTexture("rsrc/images/missing.png");
		shipsContainer->setBackground(texture);
		shipsContainer->setBackgroundRepeat(flat::sharp::ui::Widget::BackgroundRepeat::REPEAT);
		shipsContainer->setPositionPolicy(flat::sharp::ui::Widget::PositionPolicy::CENTER);
		shipsContainer->setRotationZ(M_PI / 3.f);
	
		static const char* shipNames[] = {
			"blue", "gray", "green", "pink", "red", "yellow",
			nullptr
		};
		for (int i = 0; shipNames[i]; ++i)
		{
			std::string fileName = "rsrc/images/units/ships/" + std::string(shipNames[i]) + "/texture.png";
			flat::sharp::ui::Widget* shipIcon = widgetFactory.makeImage(fileName);
			shipIcon->setPositionPolicy(flat::sharp::ui::Widget::PositionPolicy::CENTER);
			m_shipIcons.push_back(shipIcon);

			flat::sharp::ui::Widget* iconContainer = widgetFactory.makeFixedSize(shipIcon->getSize());
			iconContainer->setMargin(20.f);
			iconContainer->addChild(shipIcon);

			shipsContainer->addChild(iconContainer);

			//shipIcon->onClick.connect(this, &SelectShipState::onShipIconClicked);
			shipIcon->onClick.connect([](flat::sharp::ui::Widget*,bool& eventHandled){
				eventHandled = true;
			});
		}

		ui->addChild(shipsContainer);
	}
	
	ui->fullLayout();
	
	m_ui.reset(ui);
}

void SelectShipState::updateUi(Game *game)
{
	flat::sharp::ui::RootWidget* ui = m_ui.get();

	if (game->input->window->isResized())
		ui->fullLayout();

	ui->updateInput();

	if (game->input->mouse->isPressed(M(LEFT)))
		ui->handleClick();
}

void SelectShipState::onShipIconClicked(flat::sharp::ui::Widget* widget, bool& eventHandled)
{
	eventHandled = true;
}

void SelectShipState::drawUi()
{
	m_ui->draw(m_programRenderSettings);
}

} // states
} // game



