#pragma once

#include "../Common.h"
#include "../util/Timestep.h"

#include <SFML/Graphics.hpp>

namespace Graphics
{
	struct Animation
	{
		std::string name;
		uint xpos, ypos, stride, length, fps;
	};

	class Animator
	{
	private:
		std::vector<Animation> m_animations;
		std::string m_current;

		float m_timer = 0;
	public:
		void setAnimation(const std::string name);
		void addAnimation(const std::string& name, uint xpos, uint ypos, uint stride, uint length, uint fps);

		void update(const Timestep& ts, sf::Sprite& destsprite);
	};
}
