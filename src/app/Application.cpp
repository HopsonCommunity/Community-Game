#include "Application.h"

#include "states/StateMenu.h"
#include "states/StatePlaying.h"

#include "../util/Log.h"

Application* Application::instance = nullptr;

Application::Application(std::string&& name, const WindowSettings& settings)
	: m_title(std::move(name))
	, m_inputScheme("Controls.json")
	, m_inputManager(&m_inputScheme)
	, m_windowSettings(settings)
{
	instance = this;

	LOG_WARN("Launching window");
	LOG_WARN("------------------------------------");
	LOG_WARN("  Resolution: ", settings.width, " x ", settings.height);
	LOG_WARN("  Fullscreen: ", settings.fullscreen);
	LOG_WARN("  VSync: ", settings.vsync);
	LOG_WARN("------------------------------------");

	auto style = settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default;

	m_window.create({ settings.width, settings.height }, m_title, style);
	m_window.setVerticalSyncEnabled(settings.vsync);

	pushState(std::make_unique<State::Menu>(this, &m_window));
}

void Application::start()
{
	constexpr static auto UP_TICK = 1000.0f / 60.0f;

	sf::Clock clock;

	float timer = 0.0f;
	float upTimer = float(clock.getElapsedTime().asMilliseconds());

	uint frames = 0;
	uint updates = 0;

	Timestep timestep(static_cast<float>(clock.getElapsedTime().asMilliseconds()));
	BGM.loadMusic();
	BGM.menu.setVolume(3.0f);
	BGM.menu.setLoop(true);
	BGM.play(BGM.menu);

	while (m_window.isOpen())
	{
		m_window.clear();
		sf::Event e;
		while (m_window.pollEvent(e))
		{
			handleEvents(e);
		}
		//Runs 60 times a second
		float now = float(clock.getElapsedTime().asMilliseconds());
		if (now - upTimer > UP_TICK)
		{
			timestep.update(now);
			updates++;
			upTimer += UP_TICK;
			m_states.back()->input();
			m_states.back()->update(timestep);
		}

		//Runs as fast as possible
		frames++;
		sf::Clock frametime;
		m_states.back()->render(m_window);
		m_frameTime = float(frametime.getElapsedTime().asMilliseconds());

		// Runs each second
		if (clock.getElapsedTime().asSeconds() - timer > 1.0f)
		{
			timer += 1.0f;
			m_framesPerSecond = frames;
			m_updatesPerSecond = updates;
			m_states.back()->tick();
			LOG_INFO("FPS: ", m_framesPerSecond, ", UPS: ", m_updatesPerSecond);
			frames = 0;
			updates = 0;
		}

		m_window.display();
	}
}

void Application::handleEvents(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		m_window.close();
		break;

	case sf::Event::KeyReleased:
		switch (event.key.code)
		{
		case sf::Keyboard::E:
			m_window.close();
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}

	m_states.back()->event(event);
}

void Application::pushState(std::unique_ptr<State::Base> state)
{
	m_states.push_back(std::move(state));
}

void Application::popState()
{
	m_states.pop_back();
}

const WindowSettings& Application::getSettings() const
{
	return m_windowSettings;
}

ResourceHolder& Application::getResources()
{
	return m_resources;
}

sf::RenderWindow& Application::getWindow()
{
	return m_window;
}

void Application::setVSync(bool enabled)
{
	m_windowSettings.vsync = enabled;
	m_window.setVerticalSyncEnabled(enabled);
}

bool Application::inputPressed(std::string action)
{
	return m_inputManager.isInput(action) && m_window.hasFocus();
}

sf::Vector2i Application::mousePosition()
{
	return m_inputManager.mousePosition(m_window);
}