#pragma once

#include <math.h>

#define PI 3.14159265358f

constexpr float toRadians(float degrees)
{
	return (float)(degrees * (PI / 180.0f));
}

constexpr float toDegrees(float radians)
{
	return (float)(radians * (180.0f / PI));
}