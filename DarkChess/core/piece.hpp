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

  friend std::ostream &operator<<(std::ostream &os, ChessPiece const &cp);

private:
  PieceColour col;
  PieceType type;
};

const std::map<const PieceType, const std::string> piece_type_string({
    {PieceType::PAWN, "Pawn"},
    {PieceType::KNIGHT, "Knight"},
    {PieceType::BISHOP, "Bishop"},
    {PieceType::ROOK, "Rook"},
    {PieceType::QUEEN, "Queen"},
    {PieceType::KING, "King"},
});

const std::map<const PieceType, const char> piece_symbol_string({
    {PieceType::PAWN, 'p'},
    {PieceType::KNIGHT, 'n'},
    {PieceType::BISHOP, 'b'},
    {PieceType::ROOK, 'r'},
    {PieceType::QUEEN, 'q'},
    {PieceType::KING, 'k'},
});

const std::map<const PieceColour, const std::string> piece_colour_string({
    {PieceColour::WHITE, "White"},
    {PieceColour::BLACK, "Black"},
});

} // namespace DarkChess
