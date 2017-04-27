#pragma once

#include "StateBase.h"

#include "../../ui/UI.h"
#include "../../ui/UIButton.h"

namespace State
{
	class Menu : public Base
	{
	public:
		Menu(Application* app, sf::RenderWindow* window);

		void event(sf::Event& event) override;
		void input() override;
		void update(const Timestep& ts) override;
		void render(sf::RenderWindow& window) override;
		void tick() override;

	private:
		sf::RectangleShape m_backGround;
		
		UI::Label m_devBuildLabel;

		UI::UI m_UI;
		UI::UIButton m_singleplayer;
		UI::UIButton m_multiplayer;
		UI::UIButton m_credits;

		void singleplayerCallback();
		void multiplayerCallback() {}
		void creditsCallback() {}
	};
}