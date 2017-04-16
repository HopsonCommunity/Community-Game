#include "MoveComponent.h"

namespace Entity
{
	MoveType MoveComponent::stringToEnum(const std::string& string)
	{
		if (string == "Sine-wave")
			return MoveType::SINE_WAVE;

		return MoveType();
	}

	MoveComponent::MoveComponent(const MoveType& type)
		: type(type)
	{
	}

	MoveComponent::MoveComponent(nlohmann::json json)
		: type(stringToEnum(json["type"]))
	{
	}
}
