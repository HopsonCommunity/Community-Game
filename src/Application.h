#pragma once

#include <memory>
#include <vector>
#include <SFML\Graphics.hpp>

#include "util/Types.h"

#include "states/State_Base.h"

class Application
{
public:
	Application(std::string&& name);

	void runMainLoop();

	void pushState(std::unique_ptr<State::SBase> state);
	void popState();

private:
	uint m_framesPerSecond, m_updatesPerSecond;
	float m_frameTime;

	sf::RenderWindow m_window;

	bool m_running = 1;
	std::vector<std::unique_ptr<State::SBase>> m_states;
};
