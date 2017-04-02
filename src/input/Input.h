#pragma once

#include "InputScheme.h"

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
		Input(InputScheme* inputScheme);

		bool isInput(std::string action);
	private:
		InputScheme* m_inputScheme;
	};
}