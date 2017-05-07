#pragma once

#include "Component.h"

#include "../../util/json.hpp"

namespace Entity
{
	enum class MoveType
	{
		SINE_WAVE
	};

	class MoveComponent : public Component
	{
	public:
		MoveType type;

		float frequency = 20.0f; // Used for SINE_WAVE
		float magnitude = 0.5f; // Used for SINE_WAVE
		Vec2 direction; // Used for SINE_WAVE

		MoveType stringToEnum(const std::string& string);

		MoveComponent(const MoveType& type);
		MoveComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override
		{
			return std::make_unique<MoveComponent>(*this);
		}

		static const int ID = 4;
	};
}
