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

        SECTION("empty iterator range")
        {
            auto const src = std::vector<int>{};
            auto const rta = test_array(src.cbegin(), src.cend());
            REQUIRE(rta.empty());
        }

        SECTION("copy empty runtime_array")
        {
            auto const src = test_array{};
            auto const rta = src;
            REQUIRE(rta.empty());
        }

        SECTION("move empty runtime_array")
            {
                auto src = test_array{};
                auto const rta = std::move(src);
                REQUIRE(rta.empty());
                REQUIRE(src.empty());
                REQUIRE(src.data() == nullptr);
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

        SECTION("with another runtime_array")
        {
            SECTION("copy construct")
            {
                auto const src = test_array{1, 2, 3};
                auto const rta = src;
                REQUIRE(rta.size() == src.size());
            }

            SECTION("move construct")
            {
                auto src = test_array{1, 2, 3};
                auto const rta = std::move(src);
                REQUIRE(rta.size() == 3);
                REQUIRE(src.empty());
                REQUIRE(src.data() == nullptr);
            }
        }
    }
}

