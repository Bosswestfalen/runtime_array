#include "bosswestfalen/runtime_array.hpp"
#include "catch/catch.hpp"


using test_array = bosswestfalen::runtime_array<int>;


TEST_CASE("fill array", "[fill]")
{
    SECTION("empty runtime_array")
    {
        auto rta = test_array{};
        REQUIRE(rta.empty());
        rta.fill(1);
        REQUIRE(rta.empty());
    }

    SECTION("non-empty runtime_array")
    {
        auto rta = test_array{1,2,3};
        REQUIRE(rta.size() == 3);

        constexpr auto Value = 4;
        rta.fill(Value);
        REQUIRE(rta.size() == 3);
        REQUIRE(std::all_of(rta.cbegin(), rta.cend(), [](auto const i) { return i == Value; }));
    }
}

