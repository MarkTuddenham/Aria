#pragma once

#include <vector>
#include <map>
#include <memory>

#include "DarkChess/piece.hpp"

namespace DarkChess
{

typedef std::pair<int, int> Position;
typedef std::map<int, std::shared_ptr<ChessPiece>> BoardMap;

typedef std::vector<int> MoveList;
typedef std::map<std::shared_ptr<ChessPiece>, std::shared_ptr<MoveList>> Moves;

Position get_pos_from_index(int);
int get_index_from_pos(Position);
bool out_of_bounds(Position);

std::ostream &operator<<(std::ostream &os, Position const &pos);
Position operator+(const Position &, const Position &);
Position operator*(const Position &, const int &);
Position operator*(const int &, const Position &);

} // namespace DarkChess