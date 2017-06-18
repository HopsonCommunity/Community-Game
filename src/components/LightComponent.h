#pragma once

#include "Component.h"

#include "../maths/Color.h"
#include "../level/LightMap.h"

namespace Components
{
	class LightComponent : public Component
	{
	public:
		Level::StaticLight light;
		bool added;

	public:
		LightComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override { return std::make_unique<LightComponent>(*this); }

		static const uint ID = ComponentID::Light;
	};
}
