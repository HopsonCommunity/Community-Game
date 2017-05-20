#include "LightComponent.h"

namespace Entity
{
	LightComponent::LightComponent(nlohmann::json json)
		: added(false)
	{
		sf::Color light_color = sf::Color::White;
		if (json.find("color") == json.end())
			LOG_WARN("[JSON] Entity with LightComponent but without color! Setting to ", light_color," as default.");
		else
		{
			std::vector<nlohmann::json> rgb = json["color"];
			light_color = sf::Color(rgb[0], rgb[1], rgb[2], 255);
		}

		byte intensity = 30;

		if (json.find("intensity") == json.end())
			LOG_WARN("[JSON] Entity with LightComponent but without intensity! Setting to \"", intensity ,"\" as default.");
		else
			intensity = json["intensity"];

		light = Level::StaticLight{0, 0, light_color, intensity };
	}
}
