#pragma once

#include <memory>
#include <vector>
#include <SFML\Graphics.hpp>

#include "util/Types.h"
#include "states/State_Base.h"

class Application
{
    public:
        Application(std::string&& name);

        void runMainLoop();

        void pushState  (std::unique_ptr<State::SBase> state);
        void popState   ();

    private:
        sf::RenderWindow m_window;

        std::vector<std::unique_ptr<State::SBase>> m_states;
};
