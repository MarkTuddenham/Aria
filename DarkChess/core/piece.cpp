#include <ostream>
#include <string>

#include "DarkChess/core/piece.hpp"

namespace DarkChess
{

ChessPiece::ChessPiece(PieceColour t_col, PieceType t_type) : col(t_col), type(t_type) {}

PieceType ChessPiece::get_type() const
{
    return type;
}

PieceColour ChessPiece::get_colour() const
{
    return col;
}

const std::string ChessPiece::get_name() const
{
    return colour_to_str_repr.at(get_colour()) + " " + type_to_str_repr.at(get_type());
}

char ChessPiece::get_symbol() const
{
    char sym = type_to_symbol.at(get_type());

    if (get_colour() == PieceColour::WHITE)
        sym = static_cast<char>(toupper(sym));

    return sym;
}

std::ostream &operator<<(std::ostream &os, ChessPiece const &cp)
{
    os << cp.get_name();
    return os;
}

int get_index_from_colour(const PieceColour &colour)
{
    return static_cast<std::underlying_type<PieceColour>::type>(colour);
}

bool operator==(const ChessPiece &c1, const ChessPiece &c2)
{
    return c1.col == c2.col &&
           c1.type == c2.type;
}

} // namespace DarkChess