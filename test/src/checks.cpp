#include <catch.hpp>
#include <aria.hpp>

void print_moves(const Aria::ChessBoard &t_cb, const Aria::Position t_pos)
{
    PROFILE_FUNCTION();

    using Aria::operator<<;

    const std::shared_ptr<Aria::ChessPiece> cp = t_cb.get_piece(t_pos);
    if (!cp)
    {
        ARIA_WARN("No piece at {}.", std::to_string(t_pos));
        return;
    }

    const std::shared_ptr<Aria::MoveList> p_moves = t_cb.get_moves(t_pos);
    if (!p_moves)
    {
        ARIA_CRITICAL("Piece ({} at {}) has no moves container!",
                    cp->get_name(),
                    std::to_string(t_pos));
        return;
    }

    std::string str;

    const int num_moves = static_cast<int>(p_moves->size());

    str += "{:2d} possible move{:<1} for {:<12} at {}: ";

    for (int i : *p_moves)
        str += std::to_string(Aria::get_pos_from_index(i)) + ' ';
    // str += std::to_string(i) + ' ';

    ARIA_INFO(str,
            num_moves,
            num_moves == 1 ? "" : "s",
            cp->get_name(),
            std::to_string(t_pos));
}

TEST_CASE("kings attacking each other", "[check]")
{

    std::unique_ptr<Aria::ChessBoard> cb_from_fen =
        Aria::FEN::chess_board_from_fen(
            "8/8/8/3k1K2/8/8/8/8 w - - 0 1");

    REQUIRE(cb_from_fen);

    const std::shared_ptr<Aria::MoveList> white_king_moves = cb_from_fen->get_moves({5, 4});
    const std::shared_ptr<Aria::MoveList> black_king_moves = cb_from_fen->get_moves({3, 4});

    REQUIRE(white_king_moves);
    REQUIRE(black_king_moves);

    REQUIRE(white_king_moves->size() == 5);
    REQUIRE(black_king_moves->size() == 5);

    std::sort(begin(*white_king_moves), end(*white_king_moves));
    std::sort(begin(*black_king_moves), end(*black_king_moves));
    REQUIRE(*white_king_moves == std::vector({29, 30, 38, 45, 46}));
    REQUIRE(*black_king_moves == std::vector({26, 27, 34, 42, 43}));

    REQUIRE_FALSE(cb_from_fen->is_in_check(Aria::PieceColour::WHITE));
    REQUIRE_FALSE(cb_from_fen->is_in_check(Aria::PieceColour::BLACK));
}

TEST_CASE("King can't move into check", "[check]")
{
    std::unique_ptr<Aria::ChessBoard> cb_from_fen =
        Aria::FEN::chess_board_from_fen(
            "8/4r3/8/5K2/1k6/2b5/8/8 w - - 0 1");

    REQUIRE(cb_from_fen);

    const std::shared_ptr<Aria::MoveList> white_king_moves = cb_from_fen->get_moves({5, 4});

    REQUIRE(white_king_moves);
    REQUIRE(white_king_moves->size() == 4);

    std::sort(begin(*white_king_moves), end(*white_king_moves));
    REQUIRE(*white_king_moves == std::vector({29, 30, 38, 46}));

    REQUIRE_FALSE(cb_from_fen->is_in_check(Aria::PieceColour::WHITE));
    REQUIRE_FALSE(cb_from_fen->is_in_check(Aria::PieceColour::BLACK));
}

TEST_CASE("King can capture to leave check", "[check]")
{

    std::unique_ptr<Aria::ChessBoard> cb_from_fen =
        Aria::FEN::chess_board_from_fen(
            "8/8/5r2/5K2/1k6/8/3b4/8 w - - 0 1");

    REQUIRE(cb_from_fen);

    const std::shared_ptr<Aria::MoveList> white_king_moves = cb_from_fen->get_moves({5, 4});

    REQUIRE(white_king_moves);
    REQUIRE(white_king_moves->size() == 4);

    std::sort(begin(*white_king_moves), end(*white_king_moves));
    REQUIRE(*white_king_moves == std::vector({28, 30, 36, 45}));

    REQUIRE(cb_from_fen->is_in_check(Aria::PieceColour::WHITE));
    REQUIRE_FALSE(cb_from_fen->is_in_check(Aria::PieceColour::BLACK));
}

TEST_CASE("King can't capture defended piece", "[check]")
{

    std::unique_ptr<Aria::ChessBoard> cb_from_fen =
        Aria::FEN::chess_board_from_fen(
            "8/8/5r2/5K2/1k6/2b5/8/8 w - - 0 1");

    REQUIRE(cb_from_fen);

    const std::shared_ptr<Aria::MoveList> white_king_moves = cb_from_fen->get_moves({5, 4});

    REQUIRE(white_king_moves);
    REQUIRE(white_king_moves->size() == 3);

    std::sort(begin(*white_king_moves), end(*white_king_moves));
    REQUIRE(*white_king_moves == std::vector({28, 30, 38}));

    REQUIRE(cb_from_fen->is_in_check(Aria::PieceColour::WHITE));
    REQUIRE_FALSE(cb_from_fen->is_in_check(Aria::PieceColour::BLACK));
}

TEST_CASE("Pinned pieces can't move out of the pin", "[check]")
{

    SECTION("Knight that has no moves")
    {
        std::unique_ptr<Aria::ChessBoard> cb_from_fen =
            Aria::FEN::chess_board_from_fen(
                "8/5r2/8/5N2/1k6/5K2/8/8 w - - 0 1");

        REQUIRE(cb_from_fen);

        const std::shared_ptr<Aria::MoveList> white_knight_moves = cb_from_fen->get_moves({5, 4});

        REQUIRE(white_knight_moves);
        REQUIRE(white_knight_moves->size() == 0);

        REQUIRE_FALSE(cb_from_fen->is_in_check(Aria::PieceColour::WHITE));
        REQUIRE_FALSE(cb_from_fen->is_in_check(Aria::PieceColour::BLACK));
    }

    SECTION("Rook that has a subset of moves")
    {
        std::unique_ptr<Aria::ChessBoard> cb_from_fen =
            Aria::FEN::chess_board_from_fen(
                "8/5r2/8/5R2/1k6/5K2/8/8 w - - 0 1");

        REQUIRE(cb_from_fen);

        const std::shared_ptr<Aria::MoveList> white_rook_moves = cb_from_fen->get_moves({5, 4});

        REQUIRE(white_rook_moves);
        REQUIRE(white_rook_moves->size() == 3);

        std::sort(begin(*white_rook_moves), end(*white_rook_moves));
        REQUIRE(*white_rook_moves == std::vector({29, 45, 53}));

        REQUIRE_FALSE(cb_from_fen->is_in_check(Aria::PieceColour::WHITE));
        REQUIRE_FALSE(cb_from_fen->is_in_check(Aria::PieceColour::BLACK));
    }
}

TEST_CASE("Pieces can only move to blocking moves if the king is in check", "[check]")
{
    SECTION("No possible moves")
    {
        std::unique_ptr<Aria::ChessBoard> cb_from_fen =
            Aria::FEN::chess_board_from_fen(
                "8/5r2/8/1k3K2/8/3N4/8/8 w - - 0 1");

        REQUIRE(cb_from_fen);

        const std::shared_ptr<Aria::MoveList> white_knight_moves = cb_from_fen->get_moves({3, 2});

        REQUIRE(white_knight_moves);
        REQUIRE(white_knight_moves->size() == 0);

        REQUIRE(cb_from_fen->is_in_check(Aria::PieceColour::WHITE));
        REQUIRE_FALSE(cb_from_fen->is_in_check(Aria::PieceColour::BLACK));
    }

    SECTION("Possible moves")
    {
        std::unique_ptr<Aria::ChessBoard> cb_from_fen =
            Aria::FEN::chess_board_from_fen(
                "8/5r2/8/1k6/8/3N1K2/8/8 w - - 0 1");

        REQUIRE(cb_from_fen);

        const std::shared_ptr<Aria::MoveList> white_knight_moves = cb_from_fen->get_moves({3, 2});

        REQUIRE(white_knight_moves);
        REQUIRE(white_knight_moves->size() == 1);
        REQUIRE(*white_knight_moves == std::vector({29}));

        REQUIRE(cb_from_fen->is_in_check(Aria::PieceColour::WHITE));
        REQUIRE_FALSE(cb_from_fen->is_in_check(Aria::PieceColour::BLACK));
    }
}