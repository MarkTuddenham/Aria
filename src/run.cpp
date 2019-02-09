#include <iostream>
#include <string>

#include "board.h"
// #include "piece.h"

void printMoves(ChessBoard&, Position);

int main()
{

    std::cout << "Creating ChessBoard!" << std::endl;

    ChessBoard cb;

    cb.prettyPrint();

    std::cout << cb.getTurn() << std::endl;
    cb.move(3, 28);
    std::cout << cb.getTurn() << std::endl;
    cb.move(91, 20); // Should fail
    std::cout << cb.getTurn() << std::endl;
    cb.move({2, 6}, {2, 5});
    std::cout << cb.getTurn() << std::endl;

    cb.prettyPrint();

    std::cout << "Number of moves: " << cb.getNumMoves() << std::endl;

    Position pos = {2, 1};
    printMoves(cb, pos);

    cb.move({6, 0}, {5, 2});
    cb.move({5, 7}, {3, 2});
    cb.prettyPrint();
    printMoves(cb, pos);

    return 0;
}

void printMoves(ChessBoard &cb, Position pos)
{
    const MoveList pMoves = *cb.getMoves(pos);

    std::cout << "Moves for " << pos << ": ";
    for (auto i = pMoves.begin(); i != pMoves.end(); ++i)
    {
        Position movePos = getPosFromIndex(*i);
        std::cout << movePos << ' ';
    }
    std::cout << std::endl;
}