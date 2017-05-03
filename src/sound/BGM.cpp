#include "BGM.h"

#include "../app/Application.h"

namespace Sound 
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
	
}