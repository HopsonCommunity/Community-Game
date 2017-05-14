#pragma once

#include "Vec2.h"

#include "../Types.h"

struct Rect
{
	int32 x, y, width, height;

	Rect();
	Rect(int32 x, int32 y, int32 width, int32 height);
	Rect(Vec2 min, Vec2 max);
};