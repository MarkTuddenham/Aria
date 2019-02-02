#include "piece.h"
#include "board.h"

#include <iostream>
#include <map>

ChessBoard::ChessBoard()
{

    // Add pieces to board

    // White pawns (1,0) -> (1,7)
    for (int i = 8; i < 16; i++)
    {
        pieces.insert(std::pair<int, ChessPiece>(i, ChessPiece(WHITE, PAWN)));
    }

    // Black pawns (6,0) -> (6,7)
    for (int i = 48; i < 56; i++)
    {
        pieces.insert(std::pair<int, ChessPiece>(i, ChessPiece(BLACK, PAWN)));
    }

    // Knights
    pieces.insert(std::pair<int, ChessPiece>(1, ChessPiece(WHITE, KNIGHT)));
    pieces.insert(std::pair<int, ChessPiece>(6, ChessPiece(WHITE, KNIGHT)));
    pieces.insert(std::pair<int, ChessPiece>(57, ChessPiece(BLACK, KNIGHT)));
    pieces.insert(std::pair<int, ChessPiece>(62, ChessPiece(BLACK, KNIGHT)));

    // Bishops
    pieces.insert(std::pair<int, ChessPiece>(2, ChessPiece(WHITE, BISHOP)));
    pieces.insert(std::pair<int, ChessPiece>(5, ChessPiece(WHITE, BISHOP)));
    pieces.insert(std::pair<int, ChessPiece>(58, ChessPiece(BLACK, BISHOP)));
    pieces.insert(std::pair<int, ChessPiece>(61, ChessPiece(BLACK, BISHOP)));

    // Rooks
    pieces.insert(std::pair<int, ChessPiece>(0, ChessPiece(WHITE, ROOK)));
    pieces.insert(std::pair<int, ChessPiece>(7, ChessPiece(WHITE, ROOK)));
    pieces.insert(std::pair<int, ChessPiece>(56, ChessPiece(BLACK, ROOK)));
    pieces.insert(std::pair<int, ChessPiece>(63, ChessPiece(BLACK, ROOK)));

    // Queens
    pieces.insert(std::pair<int, ChessPiece>(3, ChessPiece(WHITE, QUEEN)));
    pieces.insert(std::pair<int, ChessPiece>(59, ChessPiece(BLACK, QUEEN)));

    // Kings
    pieces.insert(std::pair<int, ChessPiece>(4, ChessPiece(WHITE, KING)));
    pieces.insert(std::pair<int, ChessPiece>(60, ChessPiece(BLACK, KING)));

    std::cout << "Created " << pieces.size() << " pieces." << std::endl;
}

int ChessBoard::getNumMoves() const
{
    return numMoves;
}

const std::map<int, ChessPiece> *ChessBoard::getPieces() const
{
    return &pieces;
}

void ChessBoard::print(std::ostream &os) const
{
    for (auto itr = pieces.begin(); itr != pieces.end(); ++itr)
    {
        std::pair<int, int> index = getCoordsFromIndex(itr->first);
        os << '\t' << "(" << index.first << ", " << index.second << ")"
           << '\t' << itr->second << std::endl;
    }
}

void ChessBoard::print() const { print(std::cout); }

void ChessBoard::prettyPrint(std::ostream &os) const
{
    char sym;

    std::cout << "---------------------------------" << std::endl;

    for (int y = 7; y >= 0; y--)
    {
        for (int x = 7; x >= 0; x--)
        {

            try
            {
                sym = pieces.at(getIndexFromCoords(std::pair<int, int>(x, y))).getSymbol();
            }
            catch (const std::out_of_range &e)
            {
                sym = ' ';
            }

            os << "| "
               << sym
               << " ";
        }
        os << "|" << std::endl
           << "---------------------------------" << std::endl;
    }
}

void ChessBoard::prettyPrint() const { prettyPrint(std::cout); }


// Helper functions.
std::pair<int, int> getCoordsFromIndex(int index)
{
    return std::pair<int, int>(index % 8, index / 8);
}

int getIndexFromCoords(std::pair<int, int> coords)
{
    return coords.first + coords.second * 8;
}