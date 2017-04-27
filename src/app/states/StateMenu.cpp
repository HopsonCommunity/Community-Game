#include "StateMenu.h"

#include "StatePlaying.h"
#include "../Application.h"

#include "../../Common.h"
#include "../../maths/Random.h"

namespace State
{
	Menu::Menu(Application* app, sf::RenderWindow* window)
		: Base(app)
		, m_backGround(Vec2(app->getWindow().getSize().x, app->getWindow().getSize().y))
		, m_devBuildLabel(sf::Text("DEV BUILD", app->getResources().fonts.get("SourceCodePro-Regular"), 30), UI::Label::Alignment::LEFT)
		, m_UI(window)
		, m_singleplayer(UI::Label(sf::Text("Singleplayer", app->getResources().fonts.get("SourceCodePro-Regular"), 18)), sf::Rect<int>(app->getWindow().getSize().x / 2 - 75, app->getWindow().getSize().y / 2 - 30, 150, 50), METHOD(&Menu::singleplayerCallback))
		, m_multiplayer(UI::Label(sf::Text("Multiplayer", app->getResources().fonts.get("SourceCodePro-Regular"), 18)), sf::Rect<int>(app->getWindow().getSize().x / 2 - 75, app->getWindow().getSize().y / 2 + 45, 150, 50), METHOD(&Menu::multiplayerCallback))
		, m_credits(UI::Label(sf::Text("Credits", app->getResources().fonts.get("SourceCodePro-Regular"), 18)), sf::Rect<int>(app->getWindow().getSize().x / 2 - 75, app->getWindow().getSize().y / 2 + 120, 150, 50), METHOD(&Menu::creditsCallback))
	{
		m_backGround.setTexture(&app->getResources().textures.get("gui/menu/dev/background"));

		m_devBuildLabel.setPosition(Vec2(18, app->getWindow().getSize().y - 40));
		m_devBuildLabel.getText().setFillColor(sf::Color(255, 235, 0, 255));

		m_UI.addComponent(m_singleplayer);
		m_UI.addComponent(m_multiplayer);
		m_UI.addComponent(m_credits);
	}

	void Menu::event(sf::Event & event)
	{
	}

	void Menu::input()
	{
	}

	void Menu::update(const Timestep& ts)
	{
		// Fancy symbols flashing
		std::string t;
		t.push_back(Random::getRandomChar());
		t += " DEV BUILD ";
		t.push_back(Random::getRandomChar());
		m_devBuildLabel.setText(t);

		Input::Input input = Application::instance->getInputManager();
		m_UI.update(input);
	}

	void Menu::render(sf::RenderWindow& window)
	{
		window.draw(m_backGround);
		m_devBuildLabel.render(window);

		m_UI.render();
	}

	void Menu::tick()
	{
	}

	void Menu::singleplayerCallback()
	{
	}
}