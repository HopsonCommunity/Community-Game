#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "../../util/Timestep.h"
#include "../../util/Types.h"

namespace Framework
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
