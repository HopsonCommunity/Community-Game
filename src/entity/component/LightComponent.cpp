#include "LightComponent.h"

namespace Entity
{
	LightComponent::LightComponent(nlohmann::json json)
		: added(false)
	{
		std::vector<nlohmann::json> rgb = json["color"];
		light = Level::StaticLight{0, 0, sf::Color(rgb[0], rgb[1], rgb[2], 255), json["intensity"]};
	}
}
