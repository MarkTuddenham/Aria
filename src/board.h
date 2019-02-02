#pragma once

#include <vector>
#include <map>

#include "piece.h"


class ChessBoard
{
  private:
    std::map<int, ChessPiece> pieces;
    int numMoves = 0;
    PieceColour turn = WHITE; 

  public:
    ChessBoard();
    int getNumMoves() const;
    const std::map<int, ChessPiece> *getPieces() const;
    PieceColour getTurn() const;
    void move(int, int);
    void move(std::pair<int, int>, std::pair<int, int>);

    void print() const;
    void print(std::ostream&) const;
    void prettyPrint() const;
    void prettyPrint(std::ostream&) const;
};

std::pair<int, int> getCoordsFromIndex(int);
int getIndexFromCoords(std::pair<int, int> coords);