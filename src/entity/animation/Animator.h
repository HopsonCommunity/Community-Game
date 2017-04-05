#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

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
		sf::Sprite* m_sprite;
		std::vector<Animation> m_anims;
		std::string m_current;

		float m_timer = 0;

	public:
		Animator(sf::Sprite* sprite);

		void setAnim(const std::string name);
		void addAnim(const std::string& name, unsigned int xpos, unsigned int ypos, unsigned int stride, unsigned int length, unsigned int fps);

		void update(const Timestep& ts);
	};

}
