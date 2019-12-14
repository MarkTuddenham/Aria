#include <catch.hpp>
#include <DarkChess.hpp>

TEST_CASE("King oh no!1", "[check]")
{
    SECTION(" Sections")
    {
        REQUIRE(true);
    }
}

// TODO kings attacking each other
// TODO kings moving into check
// TODO pinned pieces moving out of the pin
// TODO king taking a defended piece
// TODO piece moving and king stays in check