#pragma once

#include <map>
#include <vector>

#include "../tile/tile.hpp"

struct Coord {
    Coord()  = default;
    ~Coord() = default;

    Coord(int x, int y);

    int x_, y_;
};

class Map {
  public:
    Map()  = default;
    ~Map() = default;

  private:
    std::map<Coord, Tile> map_;
};