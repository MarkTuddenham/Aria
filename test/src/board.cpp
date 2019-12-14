#include <catch.hpp>
#include <DarkChess.hpp>

TEST_CASE("Board Constructor", "[board]")
{
    DarkChess::ChessBoard cb;

    REQUIRE(cb.to_string() != "");

    SECTION(" Normally")
    {
        REQUIRE(true);
    }
}