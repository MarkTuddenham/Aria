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
        pieces.insert({i, ChessPiece(WHITE, PAWN)});
    }

    // Black pawns (6,0) -> (6,7)
    for (int i = 48; i < 56; i++)
    {
        pieces.insert({i, ChessPiece(BLACK, PAWN)});
    }

    // Knights
    pieces.insert({1, ChessPiece(WHITE, KNIGHT)});
    pieces.insert({6, ChessPiece(WHITE, KNIGHT)});
    pieces.insert({57, ChessPiece(BLACK, KNIGHT)});
    pieces.insert({62, ChessPiece(BLACK, KNIGHT)});

    // Bishops
    pieces.insert({2, ChessPiece(WHITE, BISHOP)});
    pieces.insert({5, ChessPiece(WHITE, BISHOP)});
    pieces.insert({58, ChessPiece(BLACK, BISHOP)});
    pieces.insert({61, ChessPiece(BLACK, BISHOP)});

    // Rooks
    pieces.insert({0, ChessPiece(WHITE, ROOK)});
    pieces.insert({7, ChessPiece(WHITE, ROOK)});
    pieces.insert({56, ChessPiece(BLACK, ROOK)});
    pieces.insert({63, ChessPiece(BLACK, ROOK)});

    // Queens
    pieces.insert({3, ChessPiece(WHITE, QUEEN)});
    pieces.insert({59, ChessPiece(BLACK, QUEEN)});

    // Kings
    pieces.insert({4, ChessPiece(WHITE, KING)});
    pieces.insert({60, ChessPiece(BLACK, KING)});

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

PieceColour ChessBoard::getTurn() const
{
    return turn;
}

void ChessBoard::move(int from, int to)
{
    bool doTurn = true;

    // check if there is a piece to move
    if (pieces.find(from) == pieces.end()) doTurn = false;

    // check piece is of the correct colour
    if (pieces[from].getColour() != getTurn()) doTurn = false;

    //TODO check legal move
    // if (!getLegalMoves()[from].contains(to)) doTurn = false;

    // Check piece exists
    if (doTurn)
    {
        //TODO track taken pieces

        // Add piece in its new place
        pieces[to] = pieces[from];

        // remove piece from old position
        pieces.erase(from);

        // Swap turns
        turn = PieceColour((turn + 1) % 2);
    }
}

void ChessBoard::move(std::pair<int, int> from, std::pair<int, int> to)
{
    move(getIndexFromCoords(from), getIndexFromCoords(to));
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

    os << std::endl
       << "  ---------------------------------" << std::endl;

    for (int y = 7; y >= 0; y--)
    {
        os << y << " ";
        for (int x = 0; x < 8; x++)
        {

            try
            {
                sym = pieces.at(getIndexFromCoords({x, y})).getSymbol();
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
           << "  ---------------------------------" << std::endl;
    }

    os << "    0   1   2   3   4   5   6   7  " << std::endl << std::endl;
}

void ChessBoard::prettyPrint() const { prettyPrint(std::cout); }

// Helper functions.
std::pair<int, int> getCoordsFromIndex(int index)
{
    return {index % 8, index / 8};
}

int getIndexFromCoords(std::pair<int, int> coords)
{
    return coords.first + coords.second * 8;
}