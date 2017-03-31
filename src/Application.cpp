#include "Application.h"

#include "states/State_Playing.h"

#include <iostream>

Application::Application(std::string&& name, const WindowSettings& settings)
: m_title(name)
, m_windowSettings(settings)
, m_window({settings.width, settings.height}, std::move(name), settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default)
{
	m_window.setVerticalSyncEnabled(settings.vsync);

	pushState(std::make_unique<State::SPlaying>(this));
}

void Application::start()
{
	m_running = true;

	sf::Clock clock;
	float timer = 0.0f;
	sf::Time time = clock.getElapsedTime();
	float upTimer = (float)time.asMilliseconds();
	float upTick = 1000.0f / 60.0f;
	uint frames = 0;
	uint updates = 0;

	while (m_running)
	{
		m_window.clear();
		sf::Event e;
		while (m_window.pollEvent(e))
			if (e.type == sf::Event::Closed)
				m_window.close();

		//Runs 60 times a second
		time = clock.getElapsedTime();
		float now = (float)time.asMilliseconds();
		if (now - upTimer > upTick)
		{
			onUpdate();
			updates++;
			upTimer += upTick;
		}

		//Runs as fast as possible
		{
			sf::Clock frametime;
			onRender();
			frames++;
			time = frametime.getElapsedTime();
			m_frameTime = (float)time.asMilliseconds();
			// std::cout << m_frameTime << " ms" << std::endl;
		}

		// Runs each second
		time = clock.getElapsedTime();
		if (time.asSeconds() - timer > 1.0f)
		{
			timer += 1.0f;
			m_framesPerSecond = frames;
			m_updatesPerSecond = updates;
			onTick();
			frames = 0;
			updates = 0;
		}
		m_window.display();
		if (!m_window.isOpen())
			m_running = false;
	}
}

void Application::onUpdate()
{
    m_states.back()->input();
	m_states.back()->update();
}

void Application::onRender()
{
	m_states.back()->draw();
}

void Application::onTick()
{
	std::cout << m_framesPerSecond << " fps, " << m_updatesPerSecond << " ups" << std::endl;

	// Testing VSync
	setVSync(!m_windowSettings.vsync);
}

void Application::pushState(std::unique_ptr<State::SBase> state)
{
	m_states.push_back(std::move(state));
}

void Application::popState()
{
	m_states.pop_back();
}

void Application::setVSync(bool enabled)
{
	m_windowSettings.vsync = enabled;
	m_window.setVerticalSyncEnabled(enabled);
}

void Application::setWindowTitle(const std::string& title)
{
	m_title = title;
	m_window.setTitle(title);
}
