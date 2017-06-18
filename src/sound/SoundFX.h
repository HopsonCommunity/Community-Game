#pragma once

#include <SFML/Audio.hpp>

namespace Sound 
{
	class SoundFX // Sound effects
	{
	public:
		static const sf::SoundBuffer* explosion;
		
		static void loadSounds();

	protected:
		sf::Sound m_sound;

	public:
		SoundFX(sf::Sound sound);
		~SoundFX();

		void play(const sf::SoundBuffer& buffer);
		void setVolume(float volume);
	};
}