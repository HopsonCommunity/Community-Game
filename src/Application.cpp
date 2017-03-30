#include "Application.h"

#include "states/State_Playing.h"

Application::Application(std::string&& name)
:   m_window    ({800, 600}, std::move(name))
{
    pushState(std::make_unique<State::SPlaying>(*this));
}

void Application::runMainLoop()
{
    sf::Clock gameTimer;

    while (m_window.isOpen())
    {
        m_window.clear();

        sf::Event e;
        while (m_window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }

        m_states.back()->input  ();
        m_states.back()->update ();
        m_states.back()->draw   ();

        m_window.display();
    }
}

void Application::pushState(std::unique_ptr<State::SBase> state)
{
    m_states.push_back(std::move(state));
}

void Application::popState()
{
    m_states.pop_back();
}
