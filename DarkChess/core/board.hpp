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
    const std::string &get_turn_name() const;

    const std::unique_ptr<BoardMap> get_pieces() const;
    const std::shared_ptr<ChessPiece> get_piece(int) const;
    const std::shared_ptr<ChessPiece> get_piece(const Position &) const;

    const std::shared_ptr<MoveList> get_moves(std::shared_ptr<ChessPiece>) const;
    const std::shared_ptr<MoveList> get_moves(int) const;
    const std::shared_ptr<MoveList> get_moves(const Position &) const;

    std::string to_string() const;

    ChessBoard();
    void move(int, int);
    void move(Position, Position);

    bool is_in_check(const PieceColour &) const;

private:
    BoardMap m_board;
    Moves m_moves;
    PieceColour m_turn = PieceColour::WHITE;

    bool m_is_in_check[2];
    std::shared_ptr<ChessPiece> m_kings[2];

    Moves m_threats_for_king;
    std::shared_ptr<MoveList> m_check_blocking_moves[2];
    std::map<Position, Position> m_pinned_pieces;

    int m_num_moves = 0;
    bool m_debug = false;

    ChessBoard(bool);
    void add_piece_to_board(const ChessPiece &, int);
    void set_start_configuration();
    void swap_turn();

    void generate_moves();
    void ad_infinitum(int, std::vector<Position>, std::shared_ptr<MoveList>);

    void prune_moves();
    void prune_pinned_pieces();
    void prune_king_moves();
    void prune_king_stays_in_check();

    friend class FEN;
    friend bool operator==(const ChessBoard &c1, const ChessBoard &c2);
};

bool board_map_compare(const BoardMap &, const BoardMap &);

} // namespace DarkChess
