#include "bosswestfalen/runtime_array.hpp"
#include "catch/catch.hpp"


TEST_CASE("creation of runtime_arrays", "[create]")
{
    SECTION("empty runtime_array")
    {
        auto const rta = bosswestfalen::runtime_array{};
        REQUIRE(rta.empty());
    }
}

