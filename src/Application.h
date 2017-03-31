#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "util/String.h"
#include "util/Types.h"

#include "states/State_Base.h"

#define VSYNC_ENABLED  1
#define VSYNC_DISABLED 0

class Application
{
public:
	struct WindowSettings
	{
		uint width, height;
		bool fullscreen, vsync;
	};
public:
	Application(const String& name, const WindowSettings& settings);

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
	void setWindowTitle(const String& title);
private:
	String m_title;
	WindowSettings m_windowSettings;

	uint m_framesPerSecond, m_updatesPerSecond;
	float m_frameTime;

	sf::RenderWindow m_window;

	bool m_running = 0;
	std::vector<std::unique_ptr<State::SBase>> m_states;
};
