#pragma once

constexpr float PI = 3.14159265358f;

#include "vec2.h"

inline float toRadians(float degrees)
{
	return (float)(degrees * (PI / 180.0f));
}

inline float toDegrees(float radians)
{
	return (float)(radians * (180.0f / PI));
}
