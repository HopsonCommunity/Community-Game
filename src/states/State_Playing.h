#pragma once

#include "State_Base.h"

class Application;

namespace State
{
    class SPlaying : public SBase
    {
        public:
            SPlaying(Application* app);

            void render() override;
            void update() override;
            void tick() override;
			void event(sf::Event& event) override;
        private:
            Application* m_pApplication;
    };
}
