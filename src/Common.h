#pragma once

// Constants

constexpr float TILE_SIZE = 32;

// Includes

#include "Types.h"

#include <functional>
#include <vector>
#include <memory>

// Macros

#define METHOD(x) std::bind(x, this)
#define _METHOD(x) std::bind(x, this, std::placeholders::_1)