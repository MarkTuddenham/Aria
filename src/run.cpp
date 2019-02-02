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

    std::cout << cb.getTurn() << std::endl;
    cb.move(3, 28);
    std::cout << cb.getTurn() << std::endl;
    cb.move(91, 20); // Should fail
    std::cout << cb.getTurn() << std::endl;
    cb.move({2,6}, {2,5});
    std::cout << cb.getTurn() << std::endl;


    cb.prettyPrint();


    return 0;
}