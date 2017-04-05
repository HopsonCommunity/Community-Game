#pragma once

#include <SFML/Audio.hpp>

namespace Sound
{
    namespace BGM //for long music files.
    {

        class BGM
        {
        public:
            static sf::Music challenge;
            static sf::Music lunar_streams;
            static sf::Music menu;

            static void loadMusic();

            virtual void play(sf::Music& music);
            virtual void pause(sf::Music& music);
        };
    }
}