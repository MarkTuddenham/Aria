#include <aria.hpp>
#include <iostream>

void print_moves(const Aria::ChessBoard &t_cb, const Aria::Position t_pos);

void app()
{
    PROFILE_FUNCTION();

    ARIA_INFO("Dark Chess Version {:d}.{:d}", Aria_VERSION_MAJOR, Aria_VERSION_MINOR);

    Aria::ChessBoard cb;

    ARIA_INFO(cb.to_string());

    print_moves(cb, {2, 1});

    cb.move({3, 1}, {3, 2});
    ARIA_WARN("Expecting move failure.");
    cb.move(91, 20); // Should fail
    cb.move({6, 6}, {6, 5});
    cb.move({2, 0}, {5, 3});

    ARIA_INFO(cb.to_string());

    ARIA_INFO("{} moves played", cb.get_num_moves());

    print_moves(cb, {3, 0});

    cb.move({4, 6}, {4, 5});
    cb.move({4, 1}, {4, 2});
    cb.move({5, 7}, {1, 3});
    ARIA_WARN("Should be check!");
    print_moves(cb, {4, 0});
    ARIA_INFO(cb.to_string());

    cb.move({3, 0}, {3, 1});

    ARIA_INFO(cb.to_string());
    ARIA_WARN("Queen should be pinned!");
    print_moves(cb, {3, 1});
    cb.move({1, 3}, {2, 4});
    ARIA_WARN("Queen should be un-pinned!");
    print_moves(cb, {3, 1});

    cb.move({3, 1}, {1, 3});
    cb.move({2, 4}, {4, 2});
    ARIA_INFO(cb.to_string());

    ARIA_WARN("Black king should no legal moves!");
    print_moves(cb, {4, 7});

    cb.move({1, 3}, {5, 7});
    ARIA_INFO(cb.to_string());
    ARIA_WARN("Black king is in check. Only the black king should be able to move.");
    print_moves(cb, {4, 7});
    print_moves(cb, {6, 7});
    print_moves(cb, {3, 7});

    cb.move({4, 7}, {5, 7});
    cb.move({1, 0}, {2, 2});
    cb.move({1, 6}, {1, 5});
    cb.move({2, 2}, {3, 4});
    cb.move({2, 7}, {1, 6});

    print_moves(cb, {5, 7});
    cb.move({3, 4}, {5, 5});
    print_moves(cb, {5, 7});

    cb.move({6, 7}, {7, 5});
    cb.move({5, 3}, {4, 4});
    cb.move({5, 7}, {4, 6});
    print_moves(cb, {4, 6});

    ARIA_INFO(cb.to_string());
    ARIA_INFO("{} moves played", cb.get_num_moves());
}

int main()
{
    Aria::Log::init(); // MUST, need to move to an entry point / Engine INIT
    Instrumentor::Get().BeginSession("Aria");

    app();

    Instrumentor::Get().EndSession();

    return 0;
}

void print_moves(const Aria::ChessBoard &t_cb, const Aria::Position t_pos)
{
    PROFILE_FUNCTION();

    using Aria::operator<<;

    const std::shared_ptr<Aria::ChessPiece> cp = t_cb.get_piece(t_pos);
    if (!cp)
    {
        ARIA_WARN("No piece at {}.", std::to_string(t_pos));
        return;
    }

    const std::shared_ptr<Aria::MoveList> p_moves = t_cb.get_moves(t_pos);
    if (!p_moves)
    {
        ARIA_CRITICAL("Piece ({} at {}) has no moves container!",
                      cp->get_name(),
                      std::to_string(t_pos));
        return;
    }

    std::string str;

    const int num_moves = static_cast<int>(p_moves->size());

    str += "{:2d} possible move{:<1} for {:<12} at {}: ";

    for (int i : *p_moves)
        str += std::to_string(Aria::get_pos_from_index(i)) + ' ';

    ARIA_INFO(str,
              num_moves,
              num_moves == 1 ? "" : "s",
              cp->get_name(),
              std::to_string(t_pos));
}
