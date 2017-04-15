#pragma once

class Application;

#include "../util/Timestep.h"

namespace sf
{
    //Forward declare SFML stuff
    class RenderWindow;
    class Event;
}

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

            virtual void event  (sf::Event& event) = 0;
            virtual void input  () = 0;
            virtual void update (const Timestep& ts) = 0;
            virtual void render (sf::RenderWindow& window) = 0;
			virtual void tick() = 0;

        protected:
            Application* m_pApplication;
    };
}


