#include <vector>
#include <map>
#include <memory>

#include "DarkChess/core/utils.hpp"
#include "DarkChess/core/piece.hpp"

namespace DarkChess
{

Position get_pos_from_index(int t_ind)
{
    return {t_ind % 8, t_ind / 8};
}

int get_index_from_pos(Position t_pos)
{
    return t_pos.first + t_pos.second * 8;
}

bool out_of_bounds(Position t_pos)
{
    return (
        t_pos.first < 0 ||
        t_pos.first > 7 ||
        t_pos.second < 0 ||
        t_pos.second > 7

    );
}

std::ostream &operator<<(std::ostream &os, Position const &pos)
{
    os << to_string(pos);
    return os;
}

Position operator+(const Position &p1, const Position &p2)
{
    return {p1.first + p2.first, p1.second + p2.second};
}

Position operator*(const Position &p, const int &i)
{
    return {p.first * i, p.second * i};
}

Position operator*(const int &i, const Position &p)
{
    return p * i; // use other operator overload
}

} // namespace DarkChess

namespace std
{

std::string to_string(const DarkChess::Position &pos)
{
    return "(" + std::to_string(pos.first) + "," + std::to_string(pos.second) + ")";
}

} // namespace std