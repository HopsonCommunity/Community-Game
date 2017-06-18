#pragma once

#include "Component.h"

namespace Components
{
	class LifeComponent : public Component
	{
	public:
		float life;
		bool done;
	
	public:
		LifeComponent(float life);
		LifeComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override { return std::make_unique<LifeComponent>(*this); }

		static const uint ID = ComponentID::Life;
	};
}
