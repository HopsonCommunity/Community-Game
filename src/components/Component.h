#pragma once

#include "../Common.h"

#include "../maths/maths.h"
#include "../util/json.hpp"

namespace Components
{
	namespace ComponentID
	{
		enum ComponentID : uint
		{
			AI = BIT(0),
			Inventory = BIT(1),
			Life = BIT(2),
			Light = BIT(3),
			Physics = BIT(4),
			Sprite = BIT(5),
			Stats = BIT(6),
			Script = BIT(7)
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