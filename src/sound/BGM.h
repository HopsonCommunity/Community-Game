#pragma once

#include <SFML/Audio.hpp>

namespace Sound {
namespace BGM //for music files that are too long to be loaded directly to RAM
{
	class BGM
	{
	public:
		sf::Music challenge;
		sf::Music lunar_streams;
		sf::Music menu;

		void loadMusic();

		void play(sf::Music &music);

		void pause(sf::Music &music);
	};
}
}