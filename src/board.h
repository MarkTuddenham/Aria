#pragma once

#include <vector>
#include <map>

#include "piece.h"


class ChessBoard
{
  private:
    std::map<int, ChessPiece> pieces;
    int numMoves = 0;

  public:
    ChessBoard();
    int getNumMoves() const;
    const std::map<int, ChessPiece> *getPieces() const;

    void print() const;
    void print(std::ostream&) const;
    void prettyPrint() const;
    void prettyPrint(std::ostream&) const;
};

std::pair<int, int> getCoordsFromIndex(int);
int getIndexFromCoords(std::pair<int, int> coords);