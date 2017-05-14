#include "LightComponent.h"

namespace Entity
{
	LightComponent::LightComponent(nlohmann::json json)
		: intensity(json["intensity"])
	{
		std::vector<nlohmann::json> rgb = json["color"];
		color = sf::Color(rgb[0], rgb[1], rgb[2], 255);
	}
}
