#include "bosswestfalen/runtime_array.hpp"
#include "catch/catch.hpp"
#include <vector>


using test_array = bosswestfalen::runtime_array<int>;


TEST_CASE("creation of runtime_arrays", "[create]")
{
    SECTION("empty runtime_array")
    {
        SECTION("default ctor")
        {
            auto const rta = test_array{};
            REQUIRE(rta.empty());
        }

        SECTION("pointer to zero elements")
        {
            auto const rta = test_array(nullptr, 0);
            REQUIRE(rta.empty());
        }
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

            SECTION("with pointer to data")
            {
                auto const src = std::vector{1, 2, 3};
                auto const rta = test_array(src.data(), src.size());
                REQUIRE(rta.size() == src.size());
            }

            SECTION("with iterator pair")
            {
                auto const src = std::vector{1, 2, 3};
                auto const rta = test_array(src.cbegin(), src.end());
                REQUIRE(rta.size() == src.size());
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

