#include "bosswestfalen/runtime_array.hpp"
#include "catch/catch.hpp"


using test_array = bosswestfalen::runtime_array<int>;


TEST_CASE("element access of runtime_arrays", "[access]")
{
    SECTION("runtime_array with some elements")
    {
        SECTION("get data")
        {
            SECTION("with empty array")
            {
                auto rta = test_array{};
                REQUIRE(rta.data() == nullptr);

                auto const rta_c = test_array{};
                REQUIRE(rta_c.data() == nullptr);
            }
        }
    }
}

