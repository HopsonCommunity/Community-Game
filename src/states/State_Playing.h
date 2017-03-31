#pragma once

#include "State_Base.h"

class Application;

namespace State
{
    class SPlaying : public SBase
    {
        public:
            SPlaying(Application* app);

            void event  (sf::Event& event)  override;
            void input  ()                  override;
            void update (float dt)          override;
            void render (sf::RenderWindow& window) override;

        private:
            Application* m_pApplication;
    };
}
