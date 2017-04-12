#pragma once

#include <SFML/System/Vector2.hpp>

#include "../../Application.h"

#include "../component/Components.h"

#include "../ai/pathfind/AStar.h"
#include "../../states/StatePlaying.h"

#include "../Entity.h"

namespace Framework
{
	class Zombie : public Entity
	{
	public:
		Zombie(const sf::Vector2f& position);

		void update(const Timestep& ts) override;
	};
}
