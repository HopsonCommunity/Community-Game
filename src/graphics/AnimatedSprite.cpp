#include "AnimatedSprite.h"

namespace Graphics
{
	AnimatedSprite::AnimatedSprite(sf::Image* atlas, uint frameSize, uint frameCount, uint speed)
	: m_atlas(atlas)
	, m_frameSize(frameSize)
	, m_speed(speed)
	, m_frameCount(frameCount)
	, m_currentFrame(new sf::Texture())
	{
	}

	AnimatedSprite::~AnimatedSprite()
	{
		delete m_atlas;
		delete m_currentFrame;
	}

	void AnimatedSprite::update()
	{
		m_frameCounter++; 
		if (m_frameCounter > m_speed) 
		{ 
			m_frame++; 
			m_frameCounter = 0; 
		} 
	
		if (m_frame > m_frameCount)
			m_frame = 0; 
	}

	void AnimatedSprite::glueToShape(sf::RectangleShape& shape, uint yOffset, bool flippedX)
	{
		sf::IntRect sprite_area(m_frame * 32, yOffset * 32, 32, 32);
		m_currentFrame->loadFromImage(*m_atlas, sprite_area);
		shape.setTexture(m_currentFrame);
		shape.setTextureRect(flippedX ? sf::IntRect(0, 0, 32, 32) : sf::IntRect(32, 0, -32, 32));
	}
}
