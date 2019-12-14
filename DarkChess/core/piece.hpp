#pragma once

#include <ostream>
#include <map>
#include <string>

namespace DarkChess
{

enum class PieceType
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum class PieceColour
{
    WHITE,
    BLACK
};

class ChessPiece
{

public:
    ChessPiece() = delete;
    ChessPiece(PieceColour, PieceType);

    const std::string get_name() const;
    PieceType get_type() const;
    PieceColour get_colour() const;

    char get_symbol() const;

private:
    PieceColour col;
    PieceType type;
    friend std::ostream &operator<<(std::ostream &os, ChessPiece const &cp);
    friend bool operator==(const ChessPiece &c1, const ChessPiece &c2);
};

int get_index_from_colour(const PieceColour &);

const std::map<const PieceType, const std::string> type_to_str_repr({
    {PieceType::PAWN, "Pawn"},
    {PieceType::KNIGHT, "Knight"},
    {PieceType::BISHOP, "Bishop"},
    {PieceType::ROOK, "Rook"},
    {PieceType::QUEEN, "Queen"},
    {PieceType::KING, "King"},
});

const std::map<const PieceType, const char> type_to_symbol({
    {PieceType::PAWN, 'p'},
    {PieceType::KNIGHT, 'n'},
    {PieceType::BISHOP, 'b'},
    {PieceType::ROOK, 'r'},
    {PieceType::QUEEN, 'q'},
    {PieceType::KING, 'k'},
});

const std::map<const char, const PieceType> symbol_to_type({
    {'p', PieceType::PAWN},
    {'n', PieceType::KNIGHT},
    {'b', PieceType::BISHOP},
    {'r', PieceType::ROOK},
    {'q', PieceType::QUEEN},
    {'k', PieceType::KING},
});

const std::map<const PieceColour, const std::string> colour_to_str_repr({
    {PieceColour::WHITE, "White"},
    {PieceColour::BLACK, "Black"},
});

} // namespace DarkChess
