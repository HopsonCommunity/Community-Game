#include "Rectangle.h"

Rectangle::Rectangle()
	: x(0)
	, y(0)
	, width(0)
	, height(0)
{
}

Rectangle::Rectangle(int32 x, int32 y, int32 width, int32 height)
	: x(x)
	, y(y)
	, width(width)
	, height(height)
{
}

Rectangle::Rectangle(Vec2 min, Vec2 max)
	: x((int32)min.x)
	, y((int32)min.y)
	, width((int32)max.x)
	, height((int32)max.y)
{
}