#pragma once

#include "Component.h"

#include "../../maths/Color.h"
#include "../../util/json.hpp"
#include "../../level/LightMap.h"

namespace Entity
{
	class LightComponent : public Component
	{
	public:
		Level::StaticLight light;
		bool added;
		
		LightComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override
		{
			return std::make_unique<LightComponent>(*this);
		}
		static const int ID = 20;
	};
}
