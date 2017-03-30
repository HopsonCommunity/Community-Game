#include "Application.h"

#include "states/State_Playing.h"

#include <iostream>

Application::Application(std::string&& name)
	: m_window({ 800, 600 }, std::move(name))
{
	pushState(std::make_unique<State::SPlaying>(this));
}

void Application::runMainLoop()
{
	sf::Clock clock;
	float timer = 0.0f;
	sf::Time time = clock.getElapsedTime();
	float upTimer = time.asMilliseconds();
	float upTick = 1000.0f / 60.0f;
	uint frames = 0;
	uint updates = 0;
	while (m_running)
	{
		m_window.clear();
		sf::Event e;
		while (m_window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}

		//Runs 60 times a second
		time = clock.getElapsedTime();
		float now = time.asMilliseconds();
		if (now - upTimer > upTick)
		{
			m_states.back()->update();
			updates++;
			upTimer += upTick;
		}

		//Runs as fast as possible
		{
			sf::Clock frametime;
			m_states.back()->draw();
			frames++;
			time = frametime.getElapsedTime();
			m_frameTime = time.asMilliseconds();
			// std::cout << m_frameTime << " ms" << std::endl;
		}

		// Runs each second
		time = clock.getElapsedTime();
		if (time.asSeconds() - timer > 1.0f)
		{
			timer += 1.0f;
			m_framesPerSecond = frames;
			m_updatesPerSecond = updates;
			std::cout << m_framesPerSecond << " fps, " << m_updatesPerSecond << " ups" << std::endl;
			frames = 0;
			updates = 0;
		}
		m_window.display();
		if (!m_window.isOpen())
			m_running = false;
	}
}

void Application::pushState(std::unique_ptr<State::SBase> state)
{
	m_states.push_back(std::move(state));
}

void Application::popState()
{
	m_states.pop_back();
}
