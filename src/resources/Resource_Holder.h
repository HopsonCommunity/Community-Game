#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Resource_Manager.h"

struct Resource_Holder
{
    Resource_Manager<sf::Texture>       textures;
    Resource_Manager<sf::Font>          fonts;
    Resource_Manager<sf::SoundBuffer>   soundBuffers;
};


