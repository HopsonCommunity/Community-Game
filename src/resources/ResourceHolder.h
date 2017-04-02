#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ResourceManager.h"

struct ResourceHolder
{
    ResourceHolder()
    :   textures        ("res/textures/",   ".png")
    ,   fonts           ("res/fonts/",      ".ttf")
    //,   soundBuffers  ("res/sfx/",         ".ogg")
    {}

    ResourceManager<sf::Texture>       textures;
    ResourceManager<sf::Font>          fonts;
    //ResourceManager<sf::SoundBuffer>   soundBuffers;
};


