#pragma once

#include <SFML/Audio.hpp>

namespace Sound 
{
	class SFX // Sound effects
	{
	public:
		static const sf::SoundBuffer* explosion;

		static void loadSounds();

	protected:
		sf::Sound m_sound;

	public:
		SFX(sf::Sound sound);

		virtual void play(const sf::SoundBuffer& buffer);
		virtual void setVolume(const int volume);
	};
}