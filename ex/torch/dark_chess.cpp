#include <DarkChess.hpp>
#include <iostream>

void print_moves(const DarkChess::ChessBoard &t_cb, const DarkChess::Position t_pos);

void app()
{
    PROFILE_FUNCTION();
}

int main()
{
    DarkChess::Log::init(); // MUST, need to move to an entry point / Engine INIT
    Instrumentor::Get().BeginSession("DarkChess");

    app();

    Instrumentor::Get().EndSession();

    return 0;
}

void print_moves(const DarkChess::ChessBoard &t_cb, const DarkChess::Position t_pos)
{
    PROFILE_FUNCTION();

    using DarkChess::operator<<;

    const std::shared_ptr<DarkChess::ChessPiece> cp = t_cb.get_piece(t_pos);
    if (!cp)
    {
        DC_WARN("No piece at {}.", std::to_string(t_pos));
        return;
    }

    const std::shared_ptr<DarkChess::MoveList> p_moves = t_cb.get_moves(t_pos);
    if (!p_moves)
    {
        DC_CRITICAL("Piece ({} at {}) has no moves container!",
                    cp->get_name(),
                    std::to_string(t_pos));
        return;
    }

    std::string str;

    const int num_moves = static_cast<int>(p_moves->size());

    str += "{:2d} possible move{:<1} for {:<12} at {}: ";

    for (int i : *p_moves)
        str += std::to_string(DarkChess::get_pos_from_index(i)) + ' ';

    DC_INFO(str,
            num_moves,
            num_moves == 1 ? "" : "s",
            cp->get_name(),
            std::to_string(t_pos));
}
