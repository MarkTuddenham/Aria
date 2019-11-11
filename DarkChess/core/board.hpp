#pragma once

#include <vector>
#include <memory>
#include <string>

#include "DarkChess/core/piece.hpp"
#include "DarkChess/core/utils.hpp"

namespace DarkChess
{

class ChessBoard
{

public:
  int get_num_moves() const;
  PieceColour get_turn() const;
  const std::string get_turn_name() const;

  const std::unique_ptr<BoardMap> get_pieces() const;
  const std::shared_ptr<ChessPiece> get_piece(int) const;
  const std::shared_ptr<ChessPiece> get_piece(Position) const;

  const std::shared_ptr<MoveList> get_moves(std::shared_ptr<ChessPiece>) const;
  const std::shared_ptr<MoveList> get_moves(int) const;
  const std::shared_ptr<MoveList> get_moves(Position) const;

  std::string to_string() const;

  ChessBoard();
  ChessBoard(bool);
  void move(int, int);
  void move(Position, Position);

private:
  BoardMap m_board;
  Moves m_moves;
  PieceColour m_turn = WHITE;
  int m_num_moves = 0;
  bool m_debug = false;

  void swap_turn();
  void generate_moves();
  void generate_piece_moves(int);
  void generate_piece_moves(const std::shared_ptr<ChessPiece>);
  void ad_infinitum(int, std::vector<Position>, std::shared_ptr<MoveList>, bool);
};

} // namespace DarkChess