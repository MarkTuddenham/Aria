#pragma once

#include <ostream>
#include <map>
#include <string>

namespace DarkChess
{

enum PieceType
{
  PAWN,
  KNIGHT,
  BISHOP,
  ROOK,
  QUEEN,
  KING
};

enum PieceColour
{
  WHITE,
  BLACK
};

const std::map<const PieceType, const std::string> piece_type_string({
    {PAWN, "Pawn"},
    {KNIGHT, "Knight"},
    {BISHOP, "Bishop"},
    {ROOK, "Rook"},
    {QUEEN, "Queen"},
    {KING, "King"},
});

const std::map<const PieceType, const char> piece_symbol_string({
    {PAWN, 'p'},
    {KNIGHT, 'n'},
    {BISHOP, 'b'},
    {ROOK, 'r'},
    {QUEEN, 'q'},
    {KING, 'k'},
});

const std::map<const PieceColour, const std::string> piece_colour_string({
    {WHITE, "White"},
    {BLACK, "Black"},
});

class ChessPiece
{
private:
  PieceColour col;
  PieceType type;

public:
  ChessPiece() = delete;
  ChessPiece(PieceColour, PieceType);

  const std::string get_name() const;
  PieceType get_type() const;
  PieceColour get_colour() const;

  char get_symbol() const;

  friend std::ostream &operator<<(std::ostream &os, ChessPiece const &cp);
};

} // namespace DarkChess
