#pragma once

#include <math.h>

#include <SFML/System/Vector2.hpp>

typedef sf::Vector2f Vec2;
typedef sf::Vector2i Vec2i;

inline float distance(const Vec2i& v1, const Vec2i& v2)
{
	double dx = v1.x - v2.x;
	double dy = v1.y - v2.y;
	return (float)sqrt(dx * dx + dy * dy);
}

inline float distance(const Vec2& v1, const Vec2& v2)
{
	double dx = v1.x - v2.x;
	double dy = v1.y - v2.y;
	return (float)sqrt(dx * dx + dy * dy);
}

inline float magnitude(const Vec2& vect)
{
	return float(sqrt(vect.x * vect.x + vect.y * vect.y));
}

inline void normalize(Vec2& vect)
{
	auto length = magnitude(vect);
	vect.x /= length;
	vect.y /= length;
}

inline float dot(const Vec2& a, const Vec2& b)
{
	auto x = a.x * b.x;
	auto y = a.y * b.y;

	return x + y;
}