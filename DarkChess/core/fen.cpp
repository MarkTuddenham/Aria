#include "DarkChess/core/board.hpp"
#include "DarkChess/core/fen.hpp"

namespace DarkChess
{

ChessBoard chess_board_from_fen(const std::string &fen)
{
    // TODO return by pointer?
    ChessBoard cb(false);

    cb.m_turn = PieceColour::BLACK;
    cb.m_turn = PieceColour::WHITE;

    return cb;
}

} // namespace DarkChess
