#pragma once

#include "StateBase.h"

#include "../debug/DebugMenu.h"
#include "../level/Level.h"
#include "../level/WorldGenerator/WorldGenerator.h"
#include "../ui/UI.h"
#include "../ui/UIButton.h"
#include "../ui/UISlider.h"

#include <SFML/Graphics.hpp>

class Application;

namespace State
{
    class SPlaying : public SBase
    {
        public:
			static SPlaying* instance;
			Level::Level m_level;

            SPlaying(Application* app, sf::RenderWindow& window);

            void event(sf::Event& event) override;
            void input() override;
            void update(const Timestep& ts) override;
            void render(sf::RenderWindow& window) override;
			void tick() override;

			inline sf::View& getCamera() { return m_camera; }

			void buttonCallback() { std::cout << "The testbutton has been pressed!" << std::endl; }
            void sliderCallback(float f) { std::cout << "The slider has the following value: " << f << std::endl; }

        private:
			sf::RenderWindow& m_window;
			sf::View m_camera;
            Debug::DebugMenu m_debugMenu;
            WGenerator::WorldGenerator m_worldGen;

            UI::UI m_ui;
            UI::UIButton m_button;
            UI::UISlider m_slider;

    };
}
