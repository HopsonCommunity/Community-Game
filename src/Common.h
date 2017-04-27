#pragma once

// Constants

constexpr float TILE_SIZE = 32;

// Includes

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

#include <cstddef>
#include <stdio.h>
#include <math.h>

// Macros

#define METHOD(x) std::bind(x, this)
#define _METHOD(x) std::bind(x, this, std::placeholders::_1)