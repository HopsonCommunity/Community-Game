#pragma once

#include "InputScheme.h"

#include "../../events/Events.h"

#include <SFML/Graphics.hpp>

namespace Input
{
	class Input
	{
	public:
		Input(InputScheme* inputScheme, Events::IEventListener* eventCallback, sf::RenderWindow* window);

		bool isInput(std::string action);

		void update();

		Vec2i getMouse();
		Vec2i getMouse(const sf::View& view);
	private:
		InputScheme* m_inputScheme;

		Vec2i m_mouse;
		
		std::array<bool, sf::Keyboard::KeyCount> m_keyState;

		sf::RenderWindow* m_window;
		Events::IEventListener* m_eventCallback;
	};
}