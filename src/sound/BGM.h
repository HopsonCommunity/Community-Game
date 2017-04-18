#pragma once

#include <SFML/Audio.hpp>

namespace Sound 
{
	class BGM // Background music
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