#pragma once

#include <math.h>

#include <SFML/System/Vector2.hpp>

typedef sf::Vector2f vec2;
typedef sf::Vector2i vec2i;

inline float magnitude(const vec2& vect)
{
	return float(sqrt(vect.x * vect.x + vect.y * vect.y));
}

inline void normalize(vec2& vect)
{
	auto length = magnitude(vect);
	vect.x /= length;
	vect.y /= length;
}

inline float dot(const vec2& a, const vec2& b)
{
	auto x = a.x * b.x;
	auto y = a.y * b.y;

	return x + y;
}