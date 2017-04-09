#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/main.cpp"

TEST_CASE("Main doesn't throw an exception", "[main]") {
	REQUIRE_NOTHROW(main());
}
