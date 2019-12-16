#include <iostream>

#include <aria.hpp>

void print_moves(const Aria::ChessBoard &t_cb, const Aria::Position t_pos);

void app()
{
    PROFILE_FUNCTION();
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
