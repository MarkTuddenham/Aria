#pragma once

#include <string>

class ChessPiece
{
  private:
    int pieceVal = 0;
    std::string name;

  public:
    ChessPiece();
    std::string getName() const;
    void setName(std::string name);
};