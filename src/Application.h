#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

//#include "util/std::string.h"
#include "util/Types.h"

#include "states/State_Base.h"

constexpr bool VSYNC_ENABLED  = true;
constexpr bool VSYNC_DISABLED = false;

class Application
{
public:
	struct WindowSettings
	{
		uint width, height;
		bool fullscreen, vsync;
	};
public:
	Application(std::string&& name, const WindowSettings& settings);

	void start();

	void onUpdate();
	void onRender();
	void onTick();
	void onEvent(sf::Event& event);

	void pushState(std::unique_ptr<State::SBase> state);
	void popState();

	const WindowSettings& getSettings() const { return m_windowSettings; }
	uint getFPS() { return m_framesPerSecond; }
	uint getUPS() { return m_updatesPerSecond; }
	float getFrameTime() { return m_frameTime; }

	void setVSync(bool enabled);
	void setWindowTitle(const std::string& title);
private:
	std::string m_title;
	WindowSettings m_windowSettings;

	uint m_framesPerSecond, m_updatesPerSecond;
	float m_frameTime;

	sf::RenderWindow m_window;

	bool m_running = 0;
	std::vector<std::unique_ptr<State::SBase>> m_states;
};
