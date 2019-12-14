#pragma once

#include <string>
#include "DarkChess/core/board.hpp"

namespace DarkChess
{

class FEN
{
public:
    static std::unique_ptr<ChessBoard> chess_board_from_fen(const std::string &fen);

private:
    static void set_position(const ChessBoard &, const std::string &);
};

} // namespace DarkChess
