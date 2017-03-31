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

        void onUpdate();
        void onRender();
        void onTick();
        void onEvent(sf::Event& event);

        void pushState(std::unique_ptr<State::SBase> state);
        void popState();

        ///@TODO Move these getters to the .cpp?
        const WindowSettings& getSettings() const { return m_windowSettings; }

        uint getFPS() const         { return m_framesPerSecond; }
        uint getUPS() const         { return m_updatesPerSecond; }
        float getFrameTime() const  { return m_frameTime; }

        void setVSync(bool enabled);
        void setWindowTitle(std::string&& title);

        const Resource_Holder& getResources() const { return m_resources; }

    private:
        Resource_Holder m_resources;

        std::string m_title;
        WindowSettings m_windowSettings;

        uint m_framesPerSecond;
        uint m_updatesPerSecond;
        float m_frameTime;

        sf::RenderWindow m_window;

        bool m_isRunning = true;
        std::vector<std::unique_ptr<State::SBase>> m_states;
};
