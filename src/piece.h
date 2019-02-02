#pragma once

#include <iostream>

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

class ChessPiece
{
  private:
    PieceColour col;
    PieceType type;

  public:
    ChessPiece();
    ChessPiece(PieceColour, PieceType);
    PieceType getType() const;
    PieceColour getColour() const;

    char getSymbol() const;

    friend std::ostream &operator<<(std::ostream &os, ChessPiece const &cp);
};