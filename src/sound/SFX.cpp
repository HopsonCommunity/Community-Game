//
// Temporary framework for playing sounds
//

#include "SFX.h"
#include "../Application.h"


namespace Sound
{
    namespace SFX //for short music files. Loads to memory
    {


        const sf::SoundBuffer* SFX::explosion = nullptr;
        const sf::SoundBuffer* SFX::groan = nullptr;


        void SFX::loadSounds(){
            explosion = &Application::instance->getResources().soundBuffers.get("explosion");
            groan = &Application::instance->getResources().soundBuffers.get("groan");

            sf::SoundBuffer buffer;
            sf::Sound sound;
        }

        SFX::SFX(sf::Sound sound)
                : m_sound(sound)
        {}

        void SFX::play(const sf::SoundBuffer& buffer)
        {
            m_sound.setBuffer(buffer);
            m_sound.play();
        }
        void SFX::setVolume(const int volume)
        {
            m_sound.setVolume(volume);
        }
    }
}