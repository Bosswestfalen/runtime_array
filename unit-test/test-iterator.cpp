#include "bosswestfalen/runtime_array.hpp"
#include "catch/catch.hpp"


using test_array = bosswestfalen::runtime_array<int>;


TEST_CASE("iterator usage", "[iterator]")
{
    SECTION("forward iterators")
    {
        SECTION("empty runtime_array")
        {
            auto rta = test_array{};
            REQUIRE(rta.begin() == rta.end());
        }

        SECTION("non-empty runtime_array")
        {
            constexpr auto Size = 3;
            auto const rta = test_array(Size);
            REQUIRE(std::distance(rta.begin(), rta.end()) == Size);
        }
    }
}

