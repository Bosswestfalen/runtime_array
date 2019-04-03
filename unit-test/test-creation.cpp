#include "bosswestfalen/runtime_array.hpp"
#include "catch/catch.hpp"


using test_array = bosswestfalen::runtime_array<int>;


TEST_CASE("creation of runtime_arrays", "[create]")
{
    SECTION("empty runtime_array")
    {
        auto const rta = test_array{};
        REQUIRE(rta.empty());
    }

    SECTION("non-empty runtime_array")
    {
        SECTION("with size")
        {
            constexpr auto Size = 2;
            SECTION("default construct elements")
            {
                auto const rta = test_array(Size);
                REQUIRE_FALSE(rta.empty());
                REQUIRE(rta.size() == Size);
            }

            SECTION("initialise elements with value")
            {
                auto const rta = test_array(Size, 123);
                REQUIRE_FALSE(rta.empty());
                REQUIRE(rta.size() == Size);
            }
        }

        SECTION("with initializer list")
        {
            auto const rta = test_array{1, 2, 3};
            REQUIRE_FALSE(rta.empty());
            REQUIRE(rta.size() == 3);
        }
    }
}

