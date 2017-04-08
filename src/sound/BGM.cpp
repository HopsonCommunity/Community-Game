#include "BGM.h"

#include "../Application.h"

namespace Sound
{
	void BGM::loadMusic()
	{
	    BGM::challenge.openFromFile("res/Music/challenge.ogg");
	    BGM::lunar_streams.openFromFile("res/Music/lunar_streams.ogg");
	    BGM::menu.openFromFile("res/Music/menu.ogg");
	
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