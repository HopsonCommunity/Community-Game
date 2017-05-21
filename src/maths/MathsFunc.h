#pragma once

#include <math.h>

#define PI 3.14159265358f

constexpr float toRadians(float degrees)
{
	return static_cast<float>(degrees * (PI / 180.0f));
}

constexpr float toDegrees(float radians)
{
	return static_cast<float>(radians * (180.0f / PI));
}