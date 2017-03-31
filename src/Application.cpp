#include "Application.h"

#include "states/State_Playing.h"

#include <iostream>

Application::Application(const String& name, const WindowSettings& settings)
	: m_title(name), m_windowSettings(settings), m_window({ settings.width, settings.height }, std::move(name), settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default)
{
	m_window.setVerticalSyncEnabled(settings.vsync);

	pushState(std::make_unique<State::SPlaying>(this));
}

void Application::start()
{
	m_running = true;

	sf::Clock clock;
	float timer = 0.0f;
	float upTimer = float(clock.getElapsedTime().asMilliseconds());
	float upTick = 1000.0f / 60.0f;
	uint frames = 0;
	uint updates = 0;
	while (m_running)
	{
		m_window.clear();
		sf::Event e;
		while (m_window.pollEvent(e))
			onEvent(e);

		//Runs 60 times a second
		float now = float(clock.getElapsedTime().asMilliseconds());
		if (now - upTimer > upTick)
		{
			updates++;
			upTimer += upTick;
			onUpdate();
		}

		//Runs as fast as possible
		{
			frames++;
			sf::Clock frametime;
			onRender();
			m_frameTime = float(frametime.getElapsedTime().asMilliseconds());
		}

		// Runs each second
		if (clock.getElapsedTime().asSeconds() - timer > 1.0f)
		{
			timer += 1.0f;
			m_framesPerSecond = frames;
			m_updatesPerSecond = updates;
			frames = 0;
			updates = 0;
			onTick();
		}
		m_window.display();
		if (!m_window.isOpen())
			m_running = false;
	}
}

void Application::onUpdate()
{
	m_states.back()->update();
}

void Application::onRender()
{
	m_states.back()->render();
}

void Application::onTick()
{
	m_states.back()->tick();

	printf("%d fps, %d ups\n", m_framesPerSecond, m_updatesPerSecond);
}

void Application::onEvent(sf::Event& event)
{
	if (event.type == sf::Event::Closed)
		m_window.close();
	if (event.type == sf::Event::KeyReleased)
		if (event.key.code == sf::Keyboard::Escape)
			m_window.close();

	m_states.back()->event(event);
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

void Application::setWindowTitle(const String& title)
{
	m_title = title;
	m_window.setTitle(title);
}
