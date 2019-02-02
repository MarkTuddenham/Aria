#include "piece.h"

ChessPiece::ChessPiece(){
    pieceVal = 0;
}

void ChessPiece::setName(std::string name)
{
    this->name = name;
}

std::string ChessPiece::getName() const
{
    return name;
}
