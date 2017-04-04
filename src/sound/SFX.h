// Temporary framework for playing sounds
//

#pragma once

#include <SFML/Audio.hpp>

namespace Sound
{
namespace SFX //for short music files. Loads to memory
{

        class SFX
        {
        public:
            static const sf::SoundBuffer* explosion;

            static void loadSounds();

        protected:
            sf::Sound m_sound;

        public:
            SFX(sf::Sound sound);

            virtual void play(const sf::SoundBuffer& buffer);
        };
}
}