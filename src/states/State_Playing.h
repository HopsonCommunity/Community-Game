#pragma once

#include "State_Base.h"

class Application;

namespace State
{
    class SPlaying : public SBase
    {
        public:
            SPlaying(Application* app);

            void event  (sf::Event& event) override;
            void input () override;
            void render() override;
            void update() override;

        private:
            Application* m_pApplication;
    };
}
