#include "MoveComponent.h"

namespace Framework
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

	ComponentType* MoveComponent::getStaticType()
	{
		static ComponentType type({ "Move" });
		return &type;
	}

	ComponentType * MoveComponent::getType() const
	{
		return getStaticType();
	}
}