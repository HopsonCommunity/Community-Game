#include "SoundFX.h"

#include "../app/Application.h"

namespace Sound 
{
	const sf::SoundBuffer* SoundFX::explosion = nullptr;

	void SoundFX::loadSounds() 
	{
		explosion = &Application::get().getResources().soundBuffers.get("explosion");

		sf::SoundBuffer buffer;
		sf::Sound sound;
	}

	SoundFX::SoundFX(sf::Sound sound)
		: m_sound(sound)
	{
	}

	SoundFX::~SoundFX()
	{
	}

	void SoundFX::play(const sf::SoundBuffer& buffer)
	{
		m_sound.setBuffer(buffer);
		m_sound.play();
	}

	void SoundFX::setVolume(float volume)
	{
		m_sound.setVolume(volume);
	}
}
