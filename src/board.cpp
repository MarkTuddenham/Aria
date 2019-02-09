#include "piece.hpp"
#include "board.hpp"

#include <iostream>
#include <map>

ChessBoard::ChessBoard() { init(); }
ChessBoard::ChessBoard(bool debug) : debug(debug) { init(); }

void ChessBoard::init()
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

    generateMoves();

    std::cout << "Created " << pieces.size() << " pieces." << std::endl;
}

int ChessBoard::getNumMoves() const
{
    return numMoves;
}

PieceColour ChessBoard::getTurn() const
{
    return turn;
}

const BoardMap *ChessBoard::getPieces() const
{
    return &pieces;
}

const ChessPiece *ChessBoard::getPiece(int ind) const
{
    if (pieces.find(ind) == pieces.end())
    {
        return nullptr;
    }
    else
    {
        return &getPieces()->at(ind);
    }
}

const ChessPiece *ChessBoard::getPiece(Position pos) const
{
    return getPiece(getIndexFromPos(pos));
}

void ChessBoard::move(int from, int to)
{
    // If in debug mode then can move any piece anywhere.

    // TODO raise errors instead of returns if cant move

    const ChessPiece *p = getPiece(from);

    // check if there is a piece to move
    if (!p)
        return;

    // check piece is of the correct colour
    if (!debug && p->getColour() != getTurn())
        return;

    //TODO check legal move
    // if (!debug && !getLegalMoves(from).contains(to)) return;

    {
        //TODO track taken pieces

        // Add piece in its new place
        pieces[to] = pieces[from];

        // remove piece from old position
        pieces.erase(from);

        // Swap turns
        turn = PieceColour((turn + 1) % 2);
        numMoves++;

        // TODO change this to
        //      updateMove(from)
        //      updateMove(to)
        // to cache only update the position that need it
        // instead of recalculating every piece.
        generateMoves();
    }
}

void ChessBoard::move(Position from, Position to)
{
    move(getIndexFromPos(from), getIndexFromPos(to));
}

void ChessBoard::generateMoves()
{
    for (auto itr = getPieces()->begin(); itr != getPieces()->end(); itr++)
        generatePieceMoves(itr->first);
}

void ChessBoard::generatePieceMoves(int ind)
{
    // TODO detect if places in check
    // TODO check out of bounds.

    // get piece from board
    const ChessPiece *p = getPiece(ind);

    if (!p)
        return;

    MoveList *pieceMoves = &moves[(ChessPiece *)p];
    pieceMoves->clear();

    switch (p->getType())
    {
    case PAWN:
    {
        //TODO rotate based on colour which only applies to pawns.

        int moveInd;

        // Check forward move
        moveInd = ind + 8;
        const ChessPiece *inFrontPiece = getPiece(moveInd);
        if (!inFrontPiece && !outOfBounds(moveInd))
            pieceMoves->push_back(moveInd);

        // Check capturing moves
        // if there exist a piece then the move can't be out of bounds.
        moveInd = ind + 7;
        const ChessPiece *capLeft = getPiece(moveInd);
        if (capLeft && capLeft->getColour() != p->getColour())
            pieceMoves->push_back(moveInd);

        moveInd = ind + 9;
        const ChessPiece *capRight = getPiece(moveInd);
        if (capRight && capRight->getColour() != p->getColour())
            pieceMoves->push_back(moveInd);

        // TODO en passant

        break;
    }

    case KNIGHT:
    {
        int relativeMoves[8] = {6, 15, 17, 10, -6, -15, -17, -10};

        for (int i = 0; i < 8; i++)
        {
            int absMovePos = ind + relativeMoves[i];

            if (outOfBounds(absMovePos))
                continue;

            const ChessPiece *toPiece = getPiece(absMovePos);

            // If there is not a piece, or the piece is capturable
            if (!toPiece || (toPiece && toPiece->getColour() != p->getColour()))
                pieceMoves->push_back(absMovePos);
        }
    }
    break;

    case BISHOP:
        /* code */
        break;

    case ROOK:
        /* code */
        break;

    case QUEEN:
        /* code */
        break;

    case KING:
    {
        int relativeMoves[8] = {7, 8, 9, 1, -7, -8, -9, -1};

        for (int i = 0; i < 8; i++)
        {
            int absMovePos = ind + relativeMoves[i];

            if (outOfBounds(absMovePos))
                continue;

            const ChessPiece *toPiece = getPiece(absMovePos);

            // If there is not a piece, or the piece is capturable
            if (!toPiece || (toPiece && toPiece->getColour() != p->getColour()))
                pieceMoves->push_back(absMovePos);
        }
    }
    break;

    default:
        // TODO raise error
        break;
    }
}

const MoveList *ChessBoard::getMoves(ChessPiece *p) const
{
    // TODO throw error
    if (!p)
        return nullptr;

    if (moves.find(p) == moves.end())
    {
        return nullptr;
    }
    else
    {
        return &moves.at(p);
    }
}

const MoveList *ChessBoard::getMoves(int ind) const
{
    return getMoves((ChessPiece *)getPiece(ind));
}

const MoveList *ChessBoard::getMoves(Position pos) const
{
    return getMoves(getIndexFromPos(pos));
}

void ChessBoard::print(std::ostream &os) const
{
    for (auto itr = pieces.begin(); itr != pieces.end(); ++itr)
    {
        Position pos = getPosFromIndex(itr->first);
        os << '\t' << "(" << pos.first << ", " << pos.second << ")"
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
                sym = pieces.at(getIndexFromPos({x, y})).getSymbol();
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

    os << "    0   1   2   3   4   5   6   7  " << std::endl
       << std::endl;
}

void ChessBoard::prettyPrint() const { prettyPrint(std::cout); }

// Helper functions.
Position getPosFromIndex(int ind)
{
    return {ind % 8, ind / 8};
}

int getIndexFromPos(Position pos)
{
    return pos.first + pos.second * 8;
}

bool outOfBounds(int ind)
{
    return ind < 0 || ind > 63;
}

std::ostream &operator<<(std::ostream &os, Position const &pos)
{
    os << "(" << pos.first << "," << pos.second << ")";
    return os;
}