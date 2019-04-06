#include "bosswestfalen/runtime_array.hpp"
#include "catch/catch.hpp"


using test_array = bosswestfalen::runtime_array<int>;


TEST_CASE("assign", "[assign]")
{
    SECTION("empty runtime_array")
    {
        auto src = test_array{};
        auto rta = test_array{1, 2, 3};

        SECTION("copy assign")
        {
            rta = src;
            REQUIRE(rta.empty());
        }

        SECTION("move assign")
        {
            rta = std::move(src);
            REQUIRE(rta.empty());
        }
    }

    SECTION("non-empty runtime_array")
    {
        auto src = test_array{1, 2, 3};
        auto rta = test_array{};

        SECTION("copy assign")
        {
            rta = src;
            REQUIRE(rta == src);
        }

        SECTION("move assign")
        {
            rta = std::move(src);

            REQUIRE(rta.size() == 3);
            REQUIRE(rta == test_array{1, 2, 3});
            REQUIRE(src == test_array{});
        }
    }

    SECTION("self assignment")
    {
        auto rta = test_array{1, 2, 3};
        auto& x = rta;
    
        SECTION("via copy")
        {
            rta = x;
            REQUIRE(rta.size() == 3);
            REQUIRE(rta.data() not_eq nullptr);
        }

        SECTION("via move")
        {
            rta = std::move(x);
            REQUIRE(rta.size() == 3);
            REQUIRE(rta.data() not_eq nullptr);
        }
    }

    SECTION("swap")
    {
        auto const a = test_array{1};
        auto const b = test_array{2};
        auto was_a_now_b = a;
        auto was_b_now_a = b;

        using std::swap;
        swap(was_a_now_b, was_b_now_a);

        REQUIRE(a == was_b_now_a);
        REQUIRE(b == was_a_now_b);
    }
}

