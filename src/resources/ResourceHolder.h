#pragma once

#include "ResourceManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct ResourceHolder
{
	ResourceHolder()
		: textures("res/textures/", ".png")
		, fonts("res/fonts/", ".ttf")
		, soundBuffers("res/sound/sfx/", ".ogg")
	{}

	ResourceManager<sf::Texture>       textures;
	ResourceManager<sf::Font>          fonts;
	ResourceManager<sf::SoundBuffer>   soundBuffers;
};
