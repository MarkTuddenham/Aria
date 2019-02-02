#include <iostream>
#include <string>

#include "board.h"
// #include "piece.h"

int main()
{

    std::cout << "Creating ChessBoard!" << std::endl;

    ChessBoard cb;

    std::cout << "Number of moves: " << cb.getNumMoves() << std::endl;

    cb.prettyPrint();

    return 0;
}