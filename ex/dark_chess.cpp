#include <DarkChess.hpp>

void print_moves(const DarkChess::ChessBoard &t_cb, const DarkChess::Position t_pos);

int main()
{
    DarkChess::Log::init();

    DC_INFO("Dark Chess Version {:d}.{:d}", DarkChess_VERSION_MAJOR, DarkChess_VERSION_MINOR);

    DarkChess::ChessBoard cb;

    DC_INFO(cb.to_string());

    print_moves(cb, {2, 1});

    cb.move(3, 28);
    cb.move(91, 20); // Should fail
    cb.move({2, 6}, {2, 5});

    DC_INFO(cb.to_string());

    DC_INFO("Number of moves: {}", cb.get_num_moves());

    print_moves(cb, {4, 3});

    cb.move({6, 0}, {5, 2});
    cb.move({5, 7}, {3, 2}); // Teleporting yay!
    cb.move({4, 1}, {4, 2});
    DC_INFO(cb.to_string());

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
    using DarkChess::operator<<;

    const std::shared_ptr<DarkChess::ChessPiece> cp = t_cb.get_piece(t_pos);
    const std::shared_ptr<DarkChess::MoveList> p_moves = t_cb.get_moves(t_pos);
    std::string str;

    str += std::to_string(p_moves->size()) + " possible moves for " + cp->get_name() + " at " + std::to_string(t_pos) + ": ";
    for (int i : *p_moves)
    {
        str += std::to_string(DarkChess::get_pos_from_index(i)) + ' ';
    }

    DC_INFO(str);
}
