#include "bosswestfalen/runtime_array.hpp"
#include "catch/catch.hpp"


using test_array = bosswestfalen::runtime_array<int>;


TEST_CASE("element access of runtime_arrays", "[access]")
{
    SECTION("empty runtime_array")
    {
        auto rta = test_array{};

        SECTION("get data ptr")
        {
            REQUIRE(rta.data() == nullptr);
        }

        SECTION("use at()")
        {
            REQUIRE_THROWS_AS(rta.at(0), std::out_of_range);
        }
    }


    SECTION("non-empty runtime_array")
    {
        auto rta = test_array{0, 1, 2};

        SECTION("get data ptr")
        {
            REQUIRE(rta.data() not_eq nullptr);
        }

        SECTION("get element without bounds check")
        {
            for (auto i = 0; i < 3; ++i)
            {
                REQUIRE(rta[i] == i);
            }
        }

        SECTION("get element with bounds check")
        {
            for (auto i = 0; i < 3; ++i)
            {
                REQUIRE(rta.at(i) == i);
            }
        }

        SECTION("front")
        {
            REQUIRE(rta.front() == rta[0]);
        }

        SECTION("back")
        {
            REQUIRE(rta.back() == rta[2]);
        }
    }
}

