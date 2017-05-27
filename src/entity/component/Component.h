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
			Hostile = 1 << 1,
			Life = 1 << 2,
			Light = 1 << 3,
			Physics = 1 << 4,
			Sprite = 1 << 5,
			Stats = 1 << 6,
			Script = 1 << 7
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