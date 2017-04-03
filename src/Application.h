#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "util/Types.h"
#include "states/StateBase.h"
#include "resources/ResourceHolder.h"
#include "input/InputScheme.h"
#include "input/Input.h"

constexpr bool VSYNC_ENABLED  = true;
constexpr bool VSYNC_DISABLED = false;
const std::string consoleAppInfo = "+---------------------------------------------------------------------------------------------------------------------+\n|                                   This is the console window for Project Comonidy                                   |\n+---------------------------------------------------------------------------------------------------------------------+\n";

class Application
{
    public:
        struct WindowSettings
        {
            uint width;
            uint height;
            bool isFullscreen;
            bool isVsyncEnabled;
        };

        Application(std::string&& name, const WindowSettings& settings);

        void start();

        void handleEvents (sf::Event& event);

        void pushState(std::unique_ptr<State::SBase> state);
        void popState();

        const WindowSettings& getSettings() const;
        ResourceHolder& getResources();

        void setVSync(bool enabled);

		bool inputPressed(std::string action);
    private:
        ResourceHolder m_resources;

        std::string m_title;
        WindowSettings m_windowSettings;
        sf::RenderWindow m_window;
        Input::InputScheme m_inputScheme;
		Input::Input m_inputManager;


        std::vector<std::unique_ptr<State::SBase>> m_states;
};
