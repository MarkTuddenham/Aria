#pragma once

#include "piece.h"

class ChessBoard
{
  private:
    ChessPiece *pieces;
    int numMoves = 0;

  public:
    ChessBoard();
    int getNumMoves() const;
    ChessPiece *getPieces() const;
};