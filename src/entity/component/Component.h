#pragma once

#include "../../maths/Maths.h"
#include "../../util/json.hpp"

namespace Framework
{
	struct ComponentType
	{
		std::string name;
	};

	class Component
	{
	public:
		Component() {};

		virtual ComponentType* getType() const { return nullptr; }
	};
}