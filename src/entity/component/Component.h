#pragma once

#include "../../maths/Maths.h"
#include "../../util/json.hpp"

#include <memory>

namespace Entity
{
	namespace ComponentID
	{
		enum ComponentID : uint
		{
			AI = 1 << 0,
			Animator = 1 << 1,
			Hostile = 1 << 2,
			Life = 1 << 3,
			Light = 1 << 4,
			Move = 1 << 5,
			Physics = 1 << 6,
			Player = 1 << 7,
			Sprite = 1 << 8,
			Stats = 1 << 9,
			Inventory = 1 << 10
		};
	}
	
	class Component
	{
	public:
		Component() {};
		virtual ~Component() {};

		virtual std::unique_ptr<Component> clone() { return std::make_unique<Component>(*this); };
	};
}
