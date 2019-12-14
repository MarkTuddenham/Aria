#include <catch.hpp>
#include <DarkChess.hpp>

void print_moves(const DarkChess::ChessBoard &t_cb, const DarkChess::Position t_pos)
{
    PROFILE_FUNCTION();

    using DarkChess::operator<<;

    const std::shared_ptr<DarkChess::ChessPiece> cp = t_cb.get_piece(t_pos);
    if (!cp)
    {
        DC_WARN("No piece at {}.", std::to_string(t_pos));
        return;
    }

    const std::shared_ptr<DarkChess::MoveList> p_moves = t_cb.get_moves(t_pos);
    if (!p_moves)
    {
        DC_CRITICAL("Piece ({} at {}) has no moves container!",
                    cp->get_name(),
                    std::to_string(t_pos));
        return;
    }

    std::string str;

    const int num_moves = static_cast<int>(p_moves->size());

    str += "{:2d} possible move{:<1} for {:<12} at {}: ";

    for (int i : *p_moves)
        str += std::to_string(DarkChess::get_pos_from_index(i)) + ' ';
    // str += std::to_string(i) + ' ';

    DC_INFO(str,
            num_moves,
            num_moves == 1 ? "" : "s",
            cp->get_name(),
            std::to_string(t_pos));
}

TEST_CASE("kings attacking each other", "[check]")
{

    std::unique_ptr<DarkChess::ChessBoard> cb_from_fen =
        DarkChess::FEN::chess_board_from_fen(
            "8/8/8/3k1K2/8/8/8/8 w - - 0 1");

    REQUIRE(cb_from_fen);

    const std::shared_ptr<DarkChess::MoveList> white_king_moves = cb_from_fen->get_moves({5, 4});
    const std::shared_ptr<DarkChess::MoveList> black_king_moves = cb_from_fen->get_moves({3, 4});

    REQUIRE(white_king_moves);
    REQUIRE(black_king_moves);

    REQUIRE(white_king_moves->size() == 5);
    REQUIRE(black_king_moves->size() == 5);

    REQUIRE(*white_king_moves == std::vector({29, 30, 38, 45, 46}));
    REQUIRE(*black_king_moves == std::vector({26, 27, 34, 42, 43}));
}

TEST_CASE("King can't move into check", "[check]")
{
    std::unique_ptr<DarkChess::ChessBoard> cb_from_fen =
        DarkChess::FEN::chess_board_from_fen(
            "8/4r3/8/5K2/1k6/2b5/8/8 w - - 0 1");

    REQUIRE(cb_from_fen);

    const std::shared_ptr<DarkChess::MoveList> white_king_moves = cb_from_fen->get_moves({5, 4});

    REQUIRE(white_king_moves);
    REQUIRE(white_king_moves->size() == 4);
    REQUIRE(*white_king_moves == std::vector({29, 30, 38, 46}));
}

TEST_CASE("King can capture to leave check", "[check]")
{

    std::unique_ptr<DarkChess::ChessBoard> cb_from_fen =
        DarkChess::FEN::chess_board_from_fen(
            "8/8/5r2/5K2/1k6/8/3b4/8 w - - 0 1");

    REQUIRE(cb_from_fen);

    const std::shared_ptr<DarkChess::MoveList> white_king_moves = cb_from_fen->get_moves({5, 4});

    REQUIRE(white_king_moves);
    REQUIRE(white_king_moves->size() == 4);
    REQUIRE(*white_king_moves == std::vector({28, 30, 36, 45}));
}

TEST_CASE("King can't capture defended piece", "[check]")
{

    std::unique_ptr<DarkChess::ChessBoard> cb_from_fen =
        DarkChess::FEN::chess_board_from_fen(
            "8/8/5r2/5K2/1k6/2b5/8/8 w - - 0 1");

    REQUIRE(cb_from_fen);

    const std::shared_ptr<DarkChess::MoveList> white_king_moves = cb_from_fen->get_moves({5, 4});

    REQUIRE(white_king_moves);
    REQUIRE(white_king_moves->size() == 3);
    REQUIRE(*white_king_moves == std::vector({28, 30, 38}));
}

TEST_CASE("Pinned pieces can't move out of the pin", "[check][!mayfail]")
{

    std::unique_ptr<DarkChess::ChessBoard> cb_from_fen =
        DarkChess::FEN::chess_board_from_fen(
            "8/5r2/8/5N2/1k6/5K2/8/8 w - - 0 1");

    REQUIRE(cb_from_fen);

    const std::shared_ptr<DarkChess::MoveList> white_knight_moves = cb_from_fen->get_moves({5, 4});

    print_moves(*cb_from_fen, {5, 4});
    DC_INFO(cb_from_fen->to_string());

    REQUIRE(white_knight_moves);
    REQUIRE(white_knight_moves->size() == 0);

    REQUIRE(false); // TODO king is in check when it shouldnt be!!!
}

//TODO make sure m_is_in_check is set.

// TODO pinned pieces moving out of the pin
// TODO piece moving and king stays in check