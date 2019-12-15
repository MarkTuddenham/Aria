#include <string>

#include "DarkChess/core/board.hpp"
#include "DarkChess/core/fen.hpp"
#include "DarkChess/core/log.hpp"
#include "DarkChess/core/piece.hpp"

namespace DarkChess
{

/*
Start: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
After e4 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"

1. Piece placement (from White's perspective). Each rank is described,
    starting with rank 8 and ending with rank 1; within each rank,
    the contents of each square are described from file "a" through file "h".
    Following the Standard Algebraic Notation (SAN), each piece is identified
    by a single letter taken from the standard English names
    (pawn = "P", knight = "N", bishop = "B", rook = "R", queen = "Q" and king = "K").
    White pieces are designated using upper-case letters ("PNBRQK")
    while black pieces use lowercase ("pnbrqk").
    Empty squares are noted using digits 1 through 8 (the number of empty squares),
    and "/" separates ranks.

2. Active color. "w" means White moves next, "b" means Black moves next.

3. Castling availability. If neither side can castle, this is "-".
    Otherwise, this has one or more letters: "K" (White can castle kingside),
    "Q" (White can castle queenside),
    "k" (Black can castle kingside),
    and/or "q" (Black can castle queenside).

4. En passant target square in algebraic notation.
    If there's no en passant target square, this is "-".
    If a pawn has just made a two-square move, this is the position "behind" the pawn.
    This is recorded regardless of whether there is a pawn in position to make an en passant capture.

5. Halfmove clock: This is the number of halfmoves since the last capture or pawn advance.
    This is used to determine if a draw can be claimed under the fifty-move rule.

6. Fullmove number: The number of the full move. It starts at 1, and is incremented after Black's move.

*/

std::unique_ptr<ChessBoard> FEN::chess_board_from_fen(const std::string &fen)
{
    ChessBoard cb(false);

    char delim = ' ';

    std::vector<std::string> tokens;
    std::string s = fen;
    size_t pos = 0;

    while ((pos = s.find(delim)) != std::string::npos)
    {
        tokens.emplace_back(s.substr(0, pos));
        s.erase(0, pos + 1);
    }
    tokens.emplace_back(s); // add the last token to the list

    if (tokens.size() != 6)
    {
        DC_CORE_ERROR("FEN: Not have enough terms. Expecting 6, got {}", tokens.size());
        return nullptr;
    }

    // 1.
    set_position(cb, tokens.at(0));

    // 2.
    if (tokens.at(1) == "w")
        cb.m_turn = PieceColour::WHITE;
    else if (tokens.at(1) == "b")
        cb.m_turn = PieceColour::BLACK;
    else
    {
        DC_CORE_ERROR("FEN: Invalid turn ({}).", tokens.at(1));
        return nullptr;
    }
    DC_CORE_TRACE("FEN: Set {} to move next.", colour_to_str_repr.at(cb.m_turn));

    // 3.
    DC_CORE_TRACE("FEN: Castling has not been implemented yet.");

    // 4.
    DC_CORE_TRACE("FEN: En passant has not been implemented yet.");

    // 5.
    DC_CORE_TRACE("FEN: The fifty-move rule has not been implemented yet.");

    // 6.
    int half_moves = std::stoi(tokens.at(5)) * 2;
    half_moves -= cb.m_turn == PieceColour::WHITE ? 2 : 1;
    cb.m_num_moves = half_moves;
    DC_CORE_TRACE("FEN: Moves set to: {}", cb.m_num_moves);

    cb.generate_moves();

    return std::make_unique<ChessBoard>(cb);
}

void FEN::set_position(ChessBoard &cb, const std::string &fen_pos)
{
    DC_CORE_TRACE("FEN: Setting up position: {}", fen_pos);

    int row = 7;
    int col = 0;

    for (char c : fen_pos)
    {
        int spaces = c - '0';

        if (spaces > 0 && spaces <= 8)
        {
            col += spaces;
        }
        else if (c == '/')
        {
            row--;
            col = 0;
        }
        else
        {
            PieceColour colour = isupper(c) ? PieceColour::WHITE : PieceColour::BLACK;
            PieceType type = symbol_to_type.at(tolower(c));
            cb.add_piece_to_board(ChessPiece(colour, type), get_index_from_pos({col, row}));
            col++;
        }
    }
}

} // namespace DarkChess
