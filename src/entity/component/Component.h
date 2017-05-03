#pragma once

#include "../../maths/Maths.h"
#include "../../util/json.hpp"

#include <memory>

namespace Entity
{
	class Component
	{
	public:
		Component() {};
		virtual ~Component() {};

		virtual std::unique_ptr<Component> clone() { return std::make_unique<Component>(*this); };
	};
}