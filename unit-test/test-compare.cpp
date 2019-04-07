#include "bosswestfalen/runtime_array.hpp"
#include "catch/catch.hpp"


using test_array = bosswestfalen::runtime_array<int>;


TEST_CASE("compare", "[compare]")
{
    auto const empty = test_array{};
    auto const a = test_array{1, 2, 3};
    auto const b = test_array{0, 1, 2, 3};

    SECTION("equality")
    {
        auto const empty_2 = empty;
        auto const a_2 = a;
        auto const b_2 = b;

        SECTION("equal")
        {
            REQUIRE_FALSE(empty == a);
            REQUIRE_FALSE(empty == b);
            REQUIRE_FALSE(a == b);

            REQUIRE(empty == empty_2);
            REQUIRE(a == a_2);
            REQUIRE(b == b_2);
        }
    
        SECTION("not equal")
        {
            REQUIRE(empty not_eq a);
            REQUIRE(empty not_eq b);
            REQUIRE(a not_eq b);

            REQUIRE_FALSE(empty not_eq empty_2);
            REQUIRE_FALSE(a not_eq a_2);
            REQUIRE_FALSE(b not_eq b_2);
        }

    }

    SECTION("less")
    {
        auto const c = test_array{4};

        REQUIRE_FALSE(empty < empty);
        REQUIRE_FALSE(a < a);
        REQUIRE_FALSE(a < b);
        REQUIRE_FALSE(c < a);

        REQUIRE(empty < a);
        REQUIRE(b < a);
        REQUIRE(a < c);
    }
}

