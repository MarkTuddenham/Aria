#include <catch.hpp>
#include <DarkChess.hpp>

TEST_CASE("Starting position", "[fen]")
{

    DarkChess::ChessBoard cb_start;
    std::unique_ptr<DarkChess::ChessBoard> cb_from_fen =
        DarkChess::FEN::chess_board_from_fen(
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    REQUIRE(cb_from_fen);
    REQUIRE(cb_start == *cb_from_fen);
}