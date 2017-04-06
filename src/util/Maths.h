#pragma once

#include <math.h>

constexpr float PI = 3.14159265358f;

float toRadians(float degrees)
{
	return (float)(degrees * (PI / 180.0f));
}

float toDegrees(float radians)
{
	return (float)(radians * (180.0f / PI));
}
