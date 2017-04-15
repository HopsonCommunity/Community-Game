#include "BGM.h"

#include "../Application.h"

namespace Sound {
namespace BGM
{

    void BGM::loadMusic()
    {
        BGM::challenge.openFromFile("res/music/Challenge.ogg");
        BGM::lunar_streams.openFromFile("res/music/LunarStreams.ogg");
        BGM::menu.openFromFile("res/music/Menu.ogg");

        sf::Music music;
    }

    void BGM::play(sf::Music& music)
    {
        music.play();
    }

    void BGM::pause(sf::Music& music)
    {
        music.pause();
    }
}}
