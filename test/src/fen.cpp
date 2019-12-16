#include <catch.hpp>
#include <aria.hpp>

TEST_CASE("Starting position", "[fen]")
{

    Aria::ChessBoard cb_start;
    std::unique_ptr<Aria::ChessBoard> cb_from_fen =
        Aria::FEN::chess_board_from_fen(
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    REQUIRE(cb_from_fen);
    REQUIRE(cb_start == *cb_from_fen);
}