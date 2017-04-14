#pragma once

#include <SFML/System/Vector2.hpp>

#include "Component.h"

#include "../../util/json.hpp"
#include "../../maths/Maths.h"

namespace Framework
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
		vec2 direction; // Used for SINE_WAVE
	public:
		MoveType stringToEnum(const std::string& string);

		MoveComponent(const MoveType& type);
		MoveComponent(nlohmann::json json);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}