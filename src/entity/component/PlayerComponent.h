#pragma once

#include "Component.h"

#include "../../util/json.hpp"

namespace Entity
{
	class PlayerComponent : public Component
	{
	public:
		PlayerComponent();
		PlayerComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override
		{
			return std::make_unique<PlayerComponent>(*this);
		}

		static const int ID = 5;
	};
}
