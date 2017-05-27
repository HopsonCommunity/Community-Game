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

		static void play(sf::Music &music);

		static void pause(sf::Music &music);
	};
}