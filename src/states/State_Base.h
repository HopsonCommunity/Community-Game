#pragma once

#include <SFML/Window.hpp>

class Application;

namespace State
{
    class SBase
    {
        public:
            SBase(Application* app)
            :   m_pApplication  (app)
            { }

            virtual ~SBase() = default;

            SBase(SBase& other) = delete;
            SBase& operator= (SBase& other) = delete;

            virtual void render() = 0;
            virtual void update() = 0;
            virtual void tick() = 0;
			virtual void event(sf::Event& event) = 0;
        private:
            Application* m_pApplication;
    };
}


