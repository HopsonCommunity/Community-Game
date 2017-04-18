#pragma once

#include "Vec2.h"

#include "../Types.h"

struct Rectangle
{
	int32 x, y, width, height;

	Rectangle();
	Rectangle(int32 x, int32 y, int32 width, int32 height);
	Rectangle(Vec2 min, Vec2 max);
};