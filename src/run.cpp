#include <iostream>
#include <string>

#include "board.h"
// #include "piece.h"

int main()
{

    std::cout << "Creating ChessBoard!" << std::endl;

    ChessBoard cb;

    std::cout << "Number of moves: " << cb.getNumMoves() << std::endl;

    ChessPiece p;

    p.setName("Queen");

    std::cout << "Piece: " << p.getName() << std::endl;
    std::cout << "Piece on board: " << cb.getPieces()[0].getName() << std::endl;

    return 0;
}