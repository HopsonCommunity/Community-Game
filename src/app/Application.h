#pragma once

#include "../Common.h"

#include "WindowSettings.h"
#include "states/StateBase.h"
#include "input/InputScheme.h"
#include "input/Input.h"

#include "../util/Timestep.h"
#include "../sound/BGM.h"
#include "../resources/ResourceHolder.h"
#include "../ui/UILabel.h"

constexpr bool VSYNC_ENABLED = true;
constexpr bool VSYNC_DISABLED = false;
const std::string consoleAppInfo = "+---------------------------------------------------------------------------------------------------------------------+\n|                                   This is the console window for Project Comonidy                                   |\n+---------------------------------------------------------------------------------------------------------------------+\n";

class Application
{
public:
	static Application* instance;

	Application(std::string&& name, const WindowSettings& settings);

	void start();

	void handleEvents(sf::Event& event);

	void pushState(std::unique_ptr<State::Base> state);
	void popState();

	const WindowSettings& getSettings() const;
	ResourceHolder& getResources();

	uint getFPS() const { return m_framesPerSecond; }
	uint getUPS() const { return m_updatesPerSecond; }
	float getFrameTime() const { return m_frameTime; }

	Input::Input getInputManager() const { return m_inputManager; }

	void setVSync(bool enabled);

	bool inputPressed(std::string action);
	sf::Vector2i mousePosition();

	float mouseX() { return static_cast<float>(mousePosition().x); }
	float mouseY() { return static_cast<float>(mousePosition().y); }

	float screenWidth() { return static_cast<float>(getWindow().getSize().x); }
	float screenHeight() { return static_cast<float>(getWindow().getSize().y); }

	sf::RenderWindow& getWindow();
	Sound::BGM BGM;

private:
	std::string m_title;

	uint m_framesPerSecond, m_updatesPerSecond;
	float m_frameTime;
	
	sf::View m_labelView;
	UI::Label* m_fpsLabel;
	UI::Label* m_frameTimeLabel;

	ResourceHolder m_resources;
	Input::InputScheme m_inputScheme;
	Input::Input m_inputManager;

	WindowSettings m_windowSettings;
	sf::RenderWindow m_window;
	std::vector<std::unique_ptr<State::Base>> m_states;
};
