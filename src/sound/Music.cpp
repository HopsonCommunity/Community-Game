#include "Music.h"

#include "../app/Application.h"

namespace Sound 
{
	void Music::loadMusic()
	{
		challenge.openFromFile("res/sound/music/Challenge.ogg");
		lunar_streams.openFromFile("res/sound/music/LunarStreams.ogg");
		menu.openFromFile("res/sound/music/Menu.ogg");

		sf::Music music;
	}

	void Music::play(sf::Music& music)
	{
		music.play();
	}

	void Music::pause(sf::Music& music)
	{
		music.pause();
	}
}