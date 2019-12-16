#pragma once

#include <string>
#include "Aria/core/board.hpp"

namespace Aria
{

class FEN
{
public:
    static std::unique_ptr<ChessBoard> chess_board_from_fen(const std::string &fen);

private:
    static void set_position(ChessBoard &, const std::string &);
};

} // namespace Aria
