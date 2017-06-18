#pragma once

#include <math.h>

#define PI 3.14159265358f

inline float toRadians(float degrees)
{
	return static_cast<float>(degrees * (PI / 180.0f));
}

inline float toDegrees(float radians)
{
	return static_cast<float>(radians * (180.0f / PI));
}

inline float clamp(float value, float minimum, float maximum)
{
	return (value > minimum) ? (value < maximum) ? value : maximum : minimum;
}