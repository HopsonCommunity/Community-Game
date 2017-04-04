#include "Animator.h"

#include <iostream>

namespace Framework
{

	Animator::Animator(sf::Sprite* sprite)
		: m_sprite(sprite)
	{}

	void Animator::setAnim(std::string name)
	{
		m_current = name;
	}

	void Animator::addAnim(const std::string& name, unsigned int xpos, unsigned int ypos, unsigned int stride, unsigned int length, unsigned int fps)
	{
		Animation anim;
		anim.name = name;
		anim.xpos = xpos;
		anim.ypos = ypos;
		anim.stride = stride;
		anim.length = length;
		anim.fps = fps;
		m_anims.push_back(anim);
	}

	void Animator::update(float dt)
	{
		if (m_anims.empty())
			return;

		m_timer += dt;
		Animation* anim = nullptr;
		bool animFound = false;
		for (unsigned int i = 0; i < m_anims.size(); i++)
		{
			if (m_anims[i].name == m_current)
			{
				anim = &m_anims[i];
				animFound = true;
			}
		}
		if (!animFound)
			return;

		float animLength = anim->length / (float)anim->fps;
		if (m_timer >= animLength)
			m_timer -= animLength;
		unsigned int frameIndex = (m_timer / animLength) * anim->length;
		unsigned int textureX = anim->xpos + frameIndex * anim->stride;
		unsigned int textureY = anim->ypos;
		m_sprite->setTextureRect(sf::IntRect(textureX, textureY, m_sprite->getTextureRect().width, m_sprite->getTextureRect().height));
	}

}