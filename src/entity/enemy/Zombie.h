#pragma once

#include <SFML/System/Vector2.hpp>

#include "../Entity.h"

namespace Framework
{
	class Zombie : public Entity
	{
	public:
		Zombie(const sf::Vector2f& position);

		void update(const Timestep& ts) override;

		///@TODO This shouldn't be in Zombie. Maybe some kind of 'AI types' class
		void pathFind(Entity* entity);
	};
}
