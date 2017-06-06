#include "StateMenu.h"

#include "StatePlaying.h"
#include "../Application.h"

#include "../../Common.h"
#include "../../maths/Random.h"

namespace State
{
	Menu::Menu(Application* app, sf::RenderWindow* window)
		: Base(app)
		, m_backGround(Vec2((float)app->screenWidth(), (float)app->screenHeight()))
		, m_devBuildLabel("", app->getFont("SourceCodePro-Regular"), 30, Graphics::Label::Alignment::LEFT)
		, m_singleplayerClicked(false)
	{
		using namespace Graphics;
		using namespace GUI;

		m_backGround.setTexture(&app->getTexture("gui/dev/menu_background"));

		m_devBuildLabel.setPosition(Vec2(18.f, static_cast<float>(app->screenHeight()) - 40.f));
		m_devBuildLabel.getText().setFillColor(sf::Color(255, 235, 0, 255));

		Label* singleplayer = new Label("Singleplayer", app->getFont("SourceCodePro-Regular"), 18);
		Label* multiplayer = new Label("Multiplayer", app->getFont("SourceCodePro-Regular"), 18);
		Label* credits = new Label("Credits", app->getFont("SourceCodePro-Regular"), 18);

		m_panel = new Panel();
		m_panel->add(new Button(singleplayer, { app->screenWidth() / 2 - 75, app->screenHeight() / 2 - 30, 150, 50 }, [&]() { m_singleplayerClicked = true; }));
		m_panel->add(new Button(multiplayer, { app->screenWidth() / 2 - 75, app->screenHeight() / 2 + 45, 150, 50 }, [&]() {}));
		m_panel->add(new Button(credits, { app->screenWidth() / 2 - 75, app->screenHeight() / 2 + 120, 150, 50 }, [&]() {}));
	}

	void Menu::onEvent(Events::Event& event)
	{
	}

	void Menu::update(const Timestep& ts)
	{
		std::stringstream m;
		m << Random::getRandomChar() << " DEV BUILD " << Random::getRandomChar();
		m_devBuildLabel.setText(m.str());
		
		if (m_singleplayerClicked)
		{
			Application::get().popPanel(m_panel);
			Application::get().pushState(std::make_unique<State::Playing>(&Application::get(), &Application::get().getWindow()));
		}
	}

	void Menu::render(sf::RenderWindow& window)
	{
		window.draw(m_backGround);
		m_devBuildLabel.render(window);
	}

	void Menu::tick()
	{
	}
}