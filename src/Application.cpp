#include "Application.h"
#include "level/SFX/SFX.h"
#include "states/StatePlaying.h"

#include <iostream>

Application* Application::instance = nullptr;

Application::Application(std::string&& name, const WindowSettings& settings)
:   m_title(std::move(name))
,   m_windowSettings(settings)
,	m_inputScheme("Controls.json")
,	m_inputManager(&m_inputScheme)
{
	instance = this;

    auto style  = settings.isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;

    m_window.create({ settings.width, settings.height }, m_title, style);
    m_window.setVerticalSyncEnabled(settings.isVsyncEnabled);

    pushState(std::make_unique<State::SPlaying>(this, m_window));
}

void Application::start()
{
	constexpr static auto UP_TICK = 1000.0f / 60.0f;

	sf::Clock clock;

	float timer = 0.0f;
	float upTimer = float(clock.getElapsedTime().asMilliseconds());

	uint frames = 0;
	uint updates = 0;

	float dt = clock.getElapsedTime().asMilliseconds();
	float last_time = 0.0f;
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
			updates++;
			upTimer += UP_TICK;
			m_states.back()->input();
			dt = (now - last_time) / 1000.0f; // dt in seconds
			last_time = now;
			m_states.back()->update(dt);
		}

		//Runs as fast as possible
		frames++;
		sf::Clock frametime;
		m_states.back()->render(m_window);
		// m_frameTime = float(frametime.getElapsedTime().asMilliseconds());

		// Runs each second
		if (clock.getElapsedTime().asSeconds() - timer > 1.0f)
		{
			timer += 1.0f;
			// m_framesPerSecond = frames;
			// m_updatesPerSecond = updates;
			std::cout << "FPS: " << frames << ", UPS: " << updates << std::endl;
			frames = 0;
			updates = 0;
			// onTick();
		}

		m_window.display();
	}
}

void Application::handleEvents(sf::Event& event)
{
    switch(event.type)
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

		case sf::Keyboard::S:
                    sound.loadSounds();
                    sound.play(*sound.explosion);
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

void Application::pushState(std::unique_ptr<State::SBase> state)
{
    m_states.push_back(std::move(state));
}

void Application::popState()
{
    m_states.pop_back();
}

const Application::WindowSettings& Application::getSettings() const
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
    m_windowSettings.isVsyncEnabled = enabled;
    m_window.setVerticalSyncEnabled(enabled);
}

bool Application::inputPressed(std::string action)
{
	return m_inputManager.isInput(action);
}

sf::Vector2i Application::mousePosition()
{
	return m_inputManager.mousePosition(m_window);
}
