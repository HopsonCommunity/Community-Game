#pragma once

/// Includes

#include "Types.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>

#include <vector>
#include <stack>
#include <list>
#include <map>
#include <unordered_map>
#include <memory>

#include <cstddef>
#include <stdio.h>
#include <math.h>

/// Constants

constexpr float TILE_SIZE = 32.f;

constexpr int32 LIGHT_MAX_LIGHTLEVEL = 25;
constexpr float LIGHT_ABSOLUTE = 80.f;

/// Macros

#define BIT(x) (1 << x)

#define METHOD(x) std::bind(x, this)
#define _METHOD(x) std::bind(x, this, std::placeholders::_1)

// Only usable in TileMap
#define FOR_EACH_TILE(action) for (uint x = 0; x < width; x++) { for (uint y = 0; y < height; y++) { action; } }