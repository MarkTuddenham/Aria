#include <iostream>

#include "dark_chess/config.hpp"
#include "dark_chess/board.hpp"
#include "dark_chess/utils.hpp"

void print_moves(const DarkChess::ChessBoard &t_cb, const DarkChess::Position t_pos);
using DarkChess::operator<<;

int main()
{
    std::cout << "Dark Chess Version " << DarkChess_VERSION_MAJOR << '.' << DarkChess_VERSION_MINOR << "\n";

    DarkChess::ChessBoard cb;

    cb.pretty_print();

    print_moves(cb, {2, 1});

    std::cout << cb.get_turn() << '\n';
    cb.move(3, 28); // TODO no legal move checking yet
    std::cout << cb.get_turn() << std::endl;
    cb.move(91, 20); // Should fail
    std::cout << cb.get_turn() << std::endl;
    cb.move({2, 6}, {2, 5});
    std::cout << cb.get_turn() << std::endl;

    cb.pretty_print();

    std::cout << "Number of moves: " << cb.get_num_moves() << std::endl;

    print_moves(cb, {4, 3});

    cb.move({6, 0}, {5, 2});
    cb.move({5, 7}, {3, 2}); // Teleporting yay!
    cb.move({4, 1}, {4, 2});
    cb.pretty_print();

    // Pawns
    print_moves(cb, {4, 3});
    print_moves(cb, {5, 6});

    // Knight
    print_moves(cb, {1, 0});

    // King
    print_moves(cb, {4, 0});

    // Bishop
    print_moves(cb, {5, 0});

    // Rook
    print_moves(cb, {7, 7});
    print_moves(cb, {7, 0});

    // Queen
    print_moves(cb, {4, 3});

    return 0;
}

void print_moves(const DarkChess::ChessBoard &t_cb, const DarkChess::Position t_pos)
{
    const std::shared_ptr<DarkChess::ChessPiece> cp = t_cb.get_piece(t_pos);
    const std::shared_ptr<DarkChess::MoveList> p_moves = t_cb.get_moves(t_pos);

    std::cout << p_moves->size() << " possible moves for " << *cp << " at " << t_pos << ": ";
    for (int i : *p_moves)
    {
        std::cout << DarkChess::get_pos_from_index(i) << ' ';
    }
    std::cout << std::endl;
}
