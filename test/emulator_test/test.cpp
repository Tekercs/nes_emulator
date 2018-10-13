#define CATCH_CONFIG_MAIN
#include <library.h>
#include <catch.hpp>

TEST_CASE("Testing the test setup" )
{
    REQUIRE( 1 == 1);
    REQUIRE( true == true);
}