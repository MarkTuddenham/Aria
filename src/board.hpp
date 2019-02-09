#pragma once

#include <vector>
#include <map>

#include "piece.hpp"

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
  bool debug = false;

private:
  void init();
  void generateMoves();
  void generatePieceMoves(int);
  void adInfinitum(int, Position[], int, MoveList *);

  // const functions (or ones with value return)
public:
  int getNumMoves() const;
  PieceColour getTurn() const;

  const BoardMap *getPieces() const;
  const ChessPiece *getPiece(int) const;
  const ChessPiece *getPiece(Position) const;

  const MoveList *getMoves(ChessPiece *) const;
  const MoveList *getMoves(int) const;
  const MoveList *getMoves(Position) const;
  // const MoveList *getLegalMoves(ChessPiece *) const;
  // const MoveList *getLegalMoves(int) const;
  // const MoveList *getLegalMoves(Position) const;

  void print() const;
  void print(std::ostream &) const;
  void prettyPrint() const;
  void prettyPrint(std::ostream &) const;

  // The non const methods:
  // Shouldn't be many ways to change the board state.
public:
  ChessBoard();
  ChessBoard(bool);
  void move(int, int);
  void move(Position, Position);
};

Position getPosFromIndex(int);
int getIndexFromPos(Position);
// bool outOfBounds(int);  // outOfBounds() Usually used when adding relative pos to abs pos, don't do this with indexes!
bool outOfBounds(Position);

std::ostream &operator<<(std::ostream &os, Position const &pos);
Position operator+(const Position &p1, const Position &p2);
Position operator*(const Position &p, const int &i);
Position operator*(const int &i, const Position &p);
