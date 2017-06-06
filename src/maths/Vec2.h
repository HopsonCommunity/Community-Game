#pragma once

#include "../Types.h"

#include <math.h>

#include <SFML/System/Vector2.hpp>

typedef sf::Vector2f Vec2;
typedef sf::Vector2i Vec2i;
typedef sf::Vector2<uint> Vec2ui;

inline bool operator<(const Vec2& v1, const Vec2& v2)
{
	return v1.x < v2.x && v1.y < v2.y;
}

inline bool operator>(const Vec2& v1, const Vec2& v2)
{
	return v1.x > v2.x && v1.y > v2.y;
}

inline float distance(const Vec2& v1, const Vec2& v2)
{
	double dx = v1.x - v2.x;
	double dy = v1.y - v2.y;
	return static_cast<float>(sqrt(dx * dx + dy * dy));
}

inline float distance(const Vec2i& v1, const Vec2i& v2)
{
	double dx = v1.x - v2.x;
	double dy = v1.y - v2.y;
	return static_cast<float>(sqrt(dx * dx + dy * dy));
}

inline float magnitude(const Vec2& vect)
{
	return float(sqrt(vect.x * vect.x + vect.y * vect.y));
}

inline float magnitude(const Vec2i& vect)
{
	return float(sqrt(vect.x * vect.x + vect.y * vect.y));
}

inline void normalize(Vec2& vect)
{
	auto length = magnitude(vect);
	vect.x /= length;
	vect.y /= length;
}

inline void normalize(Vec2i& vect)
{
	auto length = magnitude(vect);
	vect.x /= static_cast<int>(length);
	vect.y /= static_cast<int>(length);
}

inline float dot(const Vec2& a, const Vec2& b)
{
	auto x = a.x * b.x;
	auto y = a.y * b.y;

	return x + y;
}

inline float dot(const Vec2i& a, const Vec2i& b)
{
	auto x = a.x * b.x;
	auto y = a.y * b.y;

	return static_cast<float>(x + y);
}