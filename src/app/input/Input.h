#pragma once

#include "InputScheme.h"

#include <SFML/Graphics.hpp>

#define MOVE_UP "MOVE_UP"
#define MOVE_DOWN "MOVE_DOWN"
#define MOVE_LEFT "MOVE_LEFT"
#define MOVE_RIGHT "MOVE_RIGHT"

///@TODO: Possible make this some sort of global/static singleton.
namespace Input
{
	class Input
	{
	public:
		static Input* instance;

		Input() { instance = this; }

		Input(InputScheme* inputScheme);

		bool isInput(std::string action);

		sf::Vector2i mousePosition(sf::RenderWindow& window);
	private:
		InputScheme* m_inputScheme;
	};
}