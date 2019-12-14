#include <catch.hpp>
#include <DarkChess.hpp>

TEST_CASE("Starting position", "[fen][!mayfail]")
{

    DarkChess::ChessBoard cb_default;
    DarkChess::ChessBoard cb_from_fen = DarkChess::chess_board_from_fen(
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    REQUIRE(cb_default.to_string() == cb_from_fen.to_string());
}