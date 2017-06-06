#include "Application.h"

#include "states/StateMenu.h"
#include "states/StatePlaying.h"

#include "../util/Log.h"

Application* Application::s_instance = nullptr;

Application::Application(std::string&& name, const WindowSettings& settings)
	: m_title(std::move(name))
	, m_resources(new ResourceHolder())
	, m_inputManager(new Input::Input(new Input::InputScheme("Controls.json"), this, &m_window))
	, m_windowSettings(settings)
{
	s_instance = this;

	LOG_WARN("Launching window");
	LOG_WARN("------------------------------------");
	if (!settings.fullscreen)
		LOG_WARN("  Resolution: ", settings.width, " x ", settings.height);
	LOG_WARN("  Fullscreen: ", settings.fullscreen);
	LOG_WARN("  VSync: ", settings.vsync);
	LOG_WARN("------------------------------------");

	auto style = settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default;

	if (settings.fullscreen)
	{
		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
		m_window.create({ desktop.width, desktop.height }, m_title, style);
	}
	else
		m_window.create({ settings.width, settings.height }, m_title, style);

	m_window.setVerticalSyncEnabled(settings.vsync);

	m_uiView = sf::View(Vec2(static_cast<float>(m_window.getSize().x / 2), static_cast<float>(m_window.getSize().y / 2)), Vec2(static_cast<float>(m_window.getSize().x), static_cast<float>(m_window.getSize().y)));

	m_fpsLabel = new Graphics::Label("", getFont("SourceCodePro-Regular"), 22, Graphics::Label::Alignment::RIGHT);
	m_frameTimeLabel = new Graphics::Label("", getFont("SourceCodePro-Regular"), 22, Graphics::Label::Alignment::RIGHT);
	
	m_fpsLabel->setPosition(Vec2(m_uiView.getCenter().x + m_uiView.getSize().x / 2 - 20, m_uiView.getCenter().y - m_uiView.getSize().y / 2 + 10));
	m_frameTimeLabel->setPosition(Vec2(m_uiView.getCenter().x + m_uiView.getSize().x / 2 - 20, m_uiView.getCenter().y - m_uiView.getSize().y / 2 + 38));
	
	m_console = new Debug::Console();

	m_backgroundMusic.loadMusic();
	m_backgroundMusic.menu.setVolume(1.0f);
	m_backgroundMusic.menu.setLoop(true);
	m_backgroundMusic.play(m_backgroundMusic.menu);

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

	while (m_window.isOpen())
	{
		m_window.clear();
		m_inputManager->update();

		///Runs 60 times a second
		float now = float(clock.getElapsedTime().asMilliseconds());
		if (now - upTimer > UP_TICK)
		{
			timestep.update(now);
			updates++;
			upTimer += UP_TICK;
			// Updating
			m_states.back()->update(timestep);
			for (int32 i = m_panels.size() - 1; i >= 0; i--)
				m_panels[i]->update();
			//
		}

		///Runs as fast as possible
		frames++;
		sf::Clock frametime;

		// Rendering
		m_states.back()->render(m_window);

		// UI
		sf::View oldView = m_window.getView();
		m_window.setView(m_uiView);
		for (int32 i = m_panels.size() - 1; i >= 0; i--)
			m_panels[i]->render(m_window);
		m_fpsLabel->render(m_window);
		// Rendering 

		m_frameTime = float(frametime.getElapsedTime().asMilliseconds());
		m_frameTimeLabel->setText(std::to_string((int)round(m_frameTime)) + " ms");
		m_frameTimeLabel->render(m_window);
		
		m_window.setView(oldView);
		
		/// Runs each second
		if (clock.getElapsedTime().asSeconds() - timer > 1.0f)
		{
			timer += 1.0f;
			m_framesPerSecond = frames;
			m_updatesPerSecond = updates;

			// Ticking
			m_states.back()->tick();
			m_fpsLabel->setText(std::to_string(m_framesPerSecond)+ " fps");
			LOG_INFO("FPS: ", m_framesPerSecond, ", UPS: ", m_updatesPerSecond);
			//

			frames = 0;
			updates = 0;
		}

		m_window.display();
	}
}

void Application::onEvent(Events::Event& event)
{
	m_states.back()->onEvent(event);

	for (uint i = 0; i < m_panels.size(); i++)
		if (!event.isHandled()) 
			m_panels[i]->onEvent(event);
}

void Application::pushState(std::unique_ptr<State::Base> state)
{
	m_states.push_back(std::move(state));
}

void Application::popState()
{
	m_states.pop_back();
}

GUI::Panel* Application::pushPanel(GUI::Panel* panel)
{
	m_panels.push_back(panel);
	return panel;
}

void Application::popPanel(GUI::Panel* panel)
{
	for (uint i = 0; i < m_panels.size(); i++)
	{
		if (m_panels[i] == panel)
		{
			m_panels.erase(m_panels.begin() + i);
			delete panel;
			break;
		}
	}
}

void Application::setVSync(bool enabled)
{
	m_windowSettings.vsync = enabled;
	m_window.setVerticalSyncEnabled(enabled);
}
