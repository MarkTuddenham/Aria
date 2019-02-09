#include <iostream>
#include <string>

#include "piece.h"

ChessPiece::ChessPiece() {}
ChessPiece::ChessPiece(PieceColour col, PieceType type) : col(col), type(type) {}

PieceType ChessPiece::getType() const
{
    return type;
}

PieceColour ChessPiece::getColour() const
{
    return col;
}

char ChessPiece::getSymbol() const
{
    char sym;
    switch (getType())
    {
    case PAWN:
        sym = 'p';
        break;

    case KNIGHT:
        sym = 'n';
        break;

    case BISHOP:
        sym = 'b';
        break;

    case ROOK:
        sym = 'r';
        break;

    case QUEEN:
        sym = 'q';
        break;

    case KING:
        sym = 'k';
        break;

    default:
        sym = 'u';
        break;
    }

    if (getColour() == 0){
        sym = toupper(sym);
    }

    return sym;

}

std::ostream &operator<<(std::ostream &os, ChessPiece const &cp)
{
    std::string col, type;
    switch (cp.getType())
    {
    case PAWN:
        type = "Pawn";
        break;

    case KNIGHT:
        type = "Knight";
        break;

    case BISHOP:
        type = "Bishop";
        break;

    case ROOK:
        type = "Rook";
        break;

    case QUEEN:
        type = "Queen";
        break;

    case KING:
        type = "King";
        break;

    default:
        type = "Unkown";
        break;
    }

    switch (cp.getColour())
    {
    case WHITE:
        col = "White";
        break;

    case BLACK:
        col = "Black";
        break;

    default:
        col = "Unknown";
        break;
    }

    os << "ChessPiece: " << col << " " << type;
    return os;
}
