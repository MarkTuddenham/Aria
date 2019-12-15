#include <catch.hpp>
#include <Aria.hpp>

TEST_CASE("Board Constructor", "[board]")
{
    Aria::ChessBoard cb;

    REQUIRE(cb.to_string() != "");

    SECTION(" Normally")
    {
        REQUIRE(true);
    }
}