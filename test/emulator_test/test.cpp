#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>

TEST_CASE("Testing the test setup" )
{
    REQUIRE( 1 == 1);
    REQUIRE( true == true);
}
