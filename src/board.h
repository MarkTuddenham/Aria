#pragma once

#include <vector>
#include <map>

#include "piece.h"

typedef std::pair<int, int> Position;
typedef std::map<int, ChessPiece> BoardMap;
typedef std::vector<int> MoveList;
typedef std::map<ChessPiece *, MoveList> Moves;

class ChessBoard
{

private:
  BoardMap pieces;
  Moves moves;

  PieceColour turn = WHITE;
  int numMoves = 0;

private:
  void generateMoves();
  void generatePieceMoves(int);

public:
  ChessBoard();
  int getNumMoves() const;
  PieceColour getTurn() const;

  const BoardMap *getPieces() const;
  const ChessPiece *getPiece(int) const;
  const ChessPiece *getPiece(Position) const;

  const MoveList *getMoves(ChessPiece *) const;
  const MoveList *getMoves(int) const;
  const MoveList *getMoves(Position) const;

  void move(int, int);
  void move(Position, Position);

  void print() const;
  void print(std::ostream &) const;
  void prettyPrint() const;
  void prettyPrint(std::ostream &) const;
};

Position getPosFromIndex(int);
int getIndexFromPos(Position);
std::ostream &operator<<(std::ostream &os, Position const &pos);
