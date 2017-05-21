#include "Rectangle.h"

Rect::Rect()
	: x(0)
	, y(0)
	, width(0)
	, height(0)
{
}

Rect::Rect(int32 x, int32 y, int32 width, int32 height)
	: x(x)
	, y(y)
	, width(width)
	, height(height)
{
}

Rect::Rect(Vec2 min, Vec2 max)
	: x(int32(min.x))
	, y(int32(min.y))
	, width(int32(max.x))
	, height(int32(max.y))
{
}