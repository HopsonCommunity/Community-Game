#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "util/Types.h"
#include "states/State_Base.h"
#include "resources/Resource_Holder.h"

constexpr bool VSYNC_ENABLED  = true;
constexpr bool VSYNC_DISABLED = false;

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

        ///@TODO Move these getters to the .cpp?
        const WindowSettings& getSettings() const { return m_windowSettings; }

        void setVSync(bool enabled);

        const Resource_Holder& getResources() const { return m_resources; }

    private:
        Resource_Holder m_resources;

        std::string m_title;
        WindowSettings m_windowSettings;
        sf::RenderWindow m_window;
        std::vector<std::unique_ptr<State::SBase>> m_states;
};
