#include "Input.h"
/*

	How input works.

	Input "actions" are defined in the 'Controls.json' file.
	Actions are just std::strings that are mapped to a sf::Keyboard:Key enum.
	We query actions by using isInput(actionName) where actionName is the name
	of the action as defined in 'Controls.json'.
*/
namespace Input
{
	Input::Input(InputScheme * inputScheme)
		: m_inputScheme(inputScheme)
	{
	}

	bool Input::isInput(std::string action)
	{
		return sf::Keyboard::isKeyPressed(m_inputScheme->getKeyForAction(action));
	}

	sf::Vector2i Input::mousePosition(sf::RenderWindow& window)
	{
		return sf::Mouse::getPosition(window);
	}
}

