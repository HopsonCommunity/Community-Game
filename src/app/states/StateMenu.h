#pragma once

#include "StateBase.h"

#include "../../graphics/gui/Panel.h"
#include "../../graphics/gui/Button.h"
#include "../../graphics/gui/Slider.h"

#include "../../graphics/gui/Window.h"

namespace State
{
	class Menu : public Base
	{
	public:
		Menu(Application* app, sf::RenderWindow* window);

		void onEvent(Events::Event& event) override;
		void update(const Timestep& ts) override;
		void render(sf::RenderWindow& window) override;
		void tick() override;

	private:
		sf::RectangleShape m_backGround;
		Graphics::Label m_devBuildLabel;
		GUI::Panel* m_panel; 

		bool m_singleplayerClicked;
	};
}