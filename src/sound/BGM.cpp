#include "BGM.h"

#include "../app/Application.h"

namespace Sound 
{
	void BGM::loadMusic()
	{
		challenge.openFromFile("res/music/Challenge.ogg");
		lunar_streams.openFromFile("res/music/LunarStreams.ogg");
		menu.openFromFile("res/music/Menu.ogg");

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
}