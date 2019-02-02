#include "piece.h"
#include "board.h"

#include <iostream>

ChessBoard::ChessBoard()
{
    this->pieces = new ChessPiece[16];
    this->pieces[0].setName("Pawn");
}

int ChessBoard::getNumMoves() const
{
    return numMoves;
}

ChessPiece *ChessBoard::getPieces() const
{
    return pieces;
}
