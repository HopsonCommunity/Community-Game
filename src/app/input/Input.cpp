#include "Input.h"

#include "../Application.h"

/*
	How input works.

	Input "actions" are defined in the 'Controls.json' file.
	Actions are just std::strings that are mapped to a sf::Keyboard:Key enum.
	We query actions by using isInput(actionName) where actionName is the name
	of the action as defined in 'Controls.json'.
*/

namespace Input
{
	Input::Input(InputScheme* inputScheme, Events::IEventListener* eventCallback, sf::RenderWindow* window)
		: m_inputScheme(inputScheme)
		, m_eventCallback(eventCallback)
		, m_window(window)
	{
		m_keyState.fill(false);
	}

	bool Input::isInput(std::string action)
	{
		return sf::Keyboard::isKeyPressed(m_inputScheme->getKeyForAction(action));
	}

	void Input::update()
	{
		Vec2i mouse = sf::Mouse::getPosition(*m_window);
		if (m_mouse != mouse)
		{
			m_mouse = mouse;

			Events::Event&& event = Events::MouseMovedEvent((float)mouse.x, (float)mouse.y, sf::Mouse::isButtonPressed(sf::Mouse::Left));
			m_eventCallback->onEvent(event);
		}

		sf::Event e;
		while (m_window->pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				m_window->close();
			
			if (e.type == sf::Event::KeyPressed)
			{
				int32 repeat = m_keyState[e.key.code] ? 1 : 0;
				int32 mods = 0;
				if (e.key.shift)
					mods = mods | (int32)Events::KeyModifier::SHIFT;
				if (e.key.control)
					mods = mods | (int32)Events::KeyModifier::CONTROL;
				if (e.key.alt)
					mods = mods | (int32)Events::KeyModifier::ALT;

				if (e.key.code == sf::Keyboard::Tilde && !repeat)
					Application::get().setConsoleActive(!Application::get().isConsoleActive());

				Events::Event&& event = Events::KeyPressedEvent(e.key.code, repeat, mods);
				m_eventCallback->onEvent(event);

				m_keyState[e.key.code] = true;
			}

			if (e.type == sf::Event::KeyReleased)
			{
				Events::Event&& event = Events::KeyReleasedEvent(e.key.code);
				m_eventCallback->onEvent(event);

				m_keyState[e.key.code] = false;
			}

			if (e.type == sf::Event::MouseButtonPressed)
			{
				Events::Event&& event = Events::MousePressedEvent(e.mouseButton.button, (float)e.mouseButton.x, (float)e.mouseButton.y);
				m_eventCallback->onEvent(event);
			}

			if (e.type == sf::Event::MouseButtonReleased)
			{
				Events::Event&& event = Events::MouseReleasedEvent(e.mouseButton.button, (float)e.mouseButton.x, (float)e.mouseButton.y);
				m_eventCallback->onEvent(event);
			}
		}
	}

	Vec2i Input::getMouse()
	{
		return m_mouse;
	}

	Vec2i Input::getMouse(const sf::View& view)
	{
		return Vec2i(m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window), view));
	}
}