#pragma once

#include <SFML/Graphics/Color.hpp>

#include "../Common.h"

inline bool canMixColors(const sf::Color& c1, const sf::Color& c2)
{
	if (c2.r > c1.r) return true;
	if (c2.g > c1.g) return true;
	if (c2.b > c1.b) return true;

	return false;
}

inline sf::Color mixColors(const sf::Color& c1, const sf::Color& c2)
{
	sf::Color result;

	// result.a = 255;
	// result.r = .5f * c1.r + .5f * c2.r;
	// result.g = .5f * c1.g + .5f * c2.g;
	// result.b = .5f * c1.b + .5f * c2.b;

	result.a = 255;
	result.r = c1.r > c2.r ? c1.r : c2.r;
	result.g = c1.g > c2.g ? c1.g : c2.g;
	result.b = c1.b > c2.b ? c1.b : c2.b;

	return result;
}

inline sf::Color applyIntensity(sf::Color c, byte intensity)
{
	float k = intensity >= LIGHT_ABSOLUTE ? 1.f : static_cast<float>(intensity) / LIGHT_ABSOLUTE;

	return sf::Color(static_cast<byte>(c.r * k), static_cast<byte>(c.g * k), static_cast<byte>(c.b * k), 255);
}

inline sf::Color reapplyIntensity(sf::Color c, byte intensityOld, byte intensityNew)
{
	float k1 = intensityNew >= LIGHT_ABSOLUTE ? 1.f : static_cast<float>(intensityNew) / LIGHT_ABSOLUTE,
		k2 = intensityOld >= LIGHT_ABSOLUTE ? 1.f : static_cast<float>(intensityOld) / LIGHT_ABSOLUTE;

	return sf::Color(static_cast<byte>(c.r * k1 / k2), static_cast<byte>(c.g * k1 / k2), static_cast<byte>(c.b * k1 / k2), 255);
}
