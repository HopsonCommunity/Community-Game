#pragma once

#include <math.h>

#include <SFML/System/Vector2.hpp>

namespace Maths
{
	constexpr float PI = 3.14159265358f;

	inline float toRadians(float degrees)
	{
		return (float)(degrees * (PI / 180.0f));
	}

	inline float toDegrees(float radians)
	{
		return (float)(radians * (180.0f / PI));
	}

	template<typename T>
	inline float magnitude(const sf::Vector2<T>& vect)
	{
		return sqrt(vect.x * vect.x + vect.y * vect.y);
	}

	template<typename T>
	inline void normalize(sf::Vector2<T>& vect)
	{
		auto length = magnitude(vect);
		vect.x /= length;
		vect.y /= length;
	}

	template<typename T>
	inline T dot(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
	{
		auto x = a.x * b.x;
		auto y = a.y * b.y;

		return x + y;
	}
}
