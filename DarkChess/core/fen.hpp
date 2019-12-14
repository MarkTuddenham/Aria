#pragma once

#include "DarkChess/core/board.hpp"

namespace DarkChess
{

ChessBoard chess_board_from_fen(const std::string &fen);

} // namespace DarkChess
