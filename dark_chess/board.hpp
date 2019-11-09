#pragma once

#include <vector>
#include <memory>

#include "dark_chess/piece.hpp"
#include "dark_chess/utils.hpp"

namespace DarkChess
{

class ChessBoard
{

private:
  // std::vector<ChessPiece> m_pieces;
  BoardMap m_board;
  Moves m_moves;
  PieceColour m_turn = WHITE;
  int numMoves = 0;
  bool debug = false;

  void swap_turn();
  void generate_moves();
  void generate_piece_moves(int);
  void generate_piece_moves(const std::shared_ptr<ChessPiece>);
  void ad_infinitum(int, std::vector<Position>, std::shared_ptr<MoveList>);

  // const functions (or ones with value return)
public:
  int get_num_moves() const;
  PieceColour get_turn() const;

  const std::unique_ptr<BoardMap> get_pieces() const;
  const std::shared_ptr<ChessPiece> get_piece(int) const;
  const std::shared_ptr<ChessPiece> get_piece(Position) const;

  const std::shared_ptr<MoveList> get_moves(std::shared_ptr<ChessPiece>) const;
  const std::shared_ptr<MoveList> get_moves(int) const;
  const std::shared_ptr<MoveList> get_moves(Position) const;
  const std::shared_ptr<MoveList> get_legal_moves(std::shared_ptr<ChessPiece>) const;
  const std::shared_ptr<MoveList> get_legal_moves(int) const;
  const std::shared_ptr<MoveList> get_legal_moves(Position) const;

  void print() const;
  void print(std::ostream &) const;
  void pretty_print() const;
  void pretty_print(std::ostream &) const;

  ChessBoard();
  ChessBoard(bool);
  void move(int, int);
  void move(Position, Position);
};

} // namespace DarkChess