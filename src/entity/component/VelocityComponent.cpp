#include "VelocityComponent.h"

#include "../../util/Maths.h"

namespace Framework
{
	VelocityComponent::VelocityComponent(const sf::Vector2f& velocity)
    : velocity(velocity)
	{ }

	VelocityComponent::VelocityComponent(nlohmann::json json)
	: speed(json["speed"])
    , velocity({json["velocity"]["x"], json["velocity"]["y"]})
	{ }

	void VelocityComponent::move(float angle)
	{
		velocity.x += cos(Maths::toRadians(angle));
		velocity.y += sin(Maths::toRadians(angle));
		Maths::normalize(velocity);

		moving = true;
	}

	void VelocityComponent::move(int xa, int ya)
	{
		velocity.x += (float)xa;
		velocity.y += (float)ya;
		if (xa != 0 || ya != 0)
			Maths::normalize(velocity);

		moving = true;
	}

	ComponentType* VelocityComponent::getStaticType()
	{
		static ComponentType type({ "Velocity" });
		return &type;
	}

	ComponentType* VelocityComponent::getType() const
	{
		return getStaticType();
	}
}
