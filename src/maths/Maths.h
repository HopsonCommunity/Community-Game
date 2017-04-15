#pragma once

constexpr float PI = 3.14159265358f;

#include "Vec2.h"
#include "../util/Types.h"

constexpr float toRadians(float degrees)
{
	return (float)(degrees * (PI / 180.0f));
}

constexpr float toDegrees(float radians)
{
	return (float)(radians * (180.0f / PI));
}
