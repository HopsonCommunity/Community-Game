#include "Animator.h"

namespace Graphics
{
	void Animator::setAnimation(std::string name)
	{
		m_current = name;
	}

	void Animator::addAnimation(const std::string& name, uint xpos, uint ypos, uint stride, uint length, uint fps)
	{
		Animation anim;
		anim.name = name;
		anim.xpos = xpos;
		anim.ypos = ypos;
		anim.stride = stride;
		anim.length = length;
		anim.fps = fps;
		m_animations.push_back(anim);
	}

	void Animator::update(const Timestep& ts, sf::Sprite& destsprite)
	{
		if (m_animations.empty())
			return;

		m_timer += ts.asSeconds();
		Animation* anim = nullptr;
		bool animFound = false;
		for (uint i = 0; i < m_animations.size(); i++)
		{
			if (m_animations[i].name == m_current)
			{
				anim = &m_animations[i];
				animFound = true;
			}
		}
		if (!animFound)
			return;

		float animLength = anim->length / (float)anim->fps;
		if (m_timer >= animLength)
			m_timer -= animLength;
		uint frameIndex = static_cast<uint>((m_timer / animLength) * anim->length);
		uint textureX = anim->xpos + frameIndex * anim->stride;
		uint textureY = anim->ypos;
		destsprite.setTextureRect(sf::IntRect(textureX, textureY, destsprite.getTextureRect().width, destsprite.getTextureRect().height));
	}
}