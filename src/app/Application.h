#pragma once

#include "../Common.h"

#include "WindowSettings.h"
#include "states/StateBase.h"
#include "input/InputScheme.h"
#include "input/Input.h"

#include "../util/Timestep.h"
#include "../sound/Music.h"

#include "../resources/ResourceHolder.h"

#include "../graphics/Label.h"
#include "../graphics/gui/Panel.h"

#include "../debug/DebugConsole.h"

#include "../events/Events.h"

constexpr bool VSYNC_ENABLED = true;
constexpr bool VSYNC_DISABLED = false;

class Application : public Events::IEventListener
{
private:
	static Application* s_instance;
public:
	Application(std::string&& name, const WindowSettings& settings);

	// Running
	void start();
	void onEvent(Events::Event& event) override;
	void render();

	// States
	void pushState(std::unique_ptr<State::Base> state);
	void popState();
	GUI::Panel* pushPanel(GUI::Panel* panel);
	void popPanel(GUI::Panel* panel);

	// Input
	Input::Input* getInputManager() const { return m_inputManager; }
	float mouseX() { return (float)m_inputManager->getMouse().x; }
	float mouseY() { return (float)m_inputManager->getMouse().y; }

	// Getters
	Vec2 uiMousePos() { return Vec2(m_inputManager->getMouse(m_uiView)); }
	bool inputPressed(std::string action) { return m_inputManager->isInput(action) && m_window.hasFocus(); }
	uint getFPS() const { return m_framesPerSecond; }
	uint getUPS() const { return m_updatesPerSecond; }
	float getFrameTime() const { return m_frameTime; }
	float screenWidth() { return (float)getWindow().getSize().x; }
	float screenHeight() { return (float)getWindow().getSize().y; }
	const WindowSettings& getSettings() const { return m_windowSettings; }
	ResourceHolder& getResources() { return *m_resources; }
	sf::RenderWindow& getWindow() { return m_window; }
	bool isConsoleActive() { return m_console->isActive(); }
	const sf::Font& getFont(const std::string& name) { return m_resources->fonts.get(name); }
	const sf::Texture& getTexture(const std::string& name) { return m_resources->textures.get(name); }

	//Setters
	void setVSync(bool enabled);
	void setConsoleActive(bool active) { m_console->setActive(active); }

	static Application& get() { return *s_instance; }

private:
	std::string m_title;

	uint frames = 0;
	uint m_framesPerSecond, m_updatesPerSecond;
	float m_frameTime;

	sf::View m_uiView;
	Graphics::Label* m_fpsLabel;
	Graphics::Label* m_frameTimeLabel;

	Debug::Console* m_console;

	Input::Input* m_inputManager;

	ResourceHolder* m_resources;
	Sound::Music m_backgroundMusic;

	WindowSettings m_windowSettings;
	sf::RenderWindow m_window;
	std::vector<std::unique_ptr<State::Base>> m_states;
	std::vector<GUI::Panel*> m_panels;
};
