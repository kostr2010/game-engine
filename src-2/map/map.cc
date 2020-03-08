/*
#pragma once;

#include <map>
#include "../tile/tile.hpp"

class Coord {
  public:
    Coord(int x, int y);
    ~Coord() = default;

    void CoordSet(int pos_x, int pos_y);
    int  CoordGetX();
    int  CoordGetY();

  private:
    int pos_x_, pos_y_;

  protected:
};

class Map {
  Map(std::vector<Tile> tiles);
    ~Map() = default;

    Entity GetEntity(std::vector<int> path);
    bool   ApplyAbility(std::vector<int> path_origin, std::vector<int> path_target,
                        AbilityKindEntityActive ability_kind);

    bool PushEntity(std::vector<int> path, Entity& entity);

  private:
    std::map<Coord, Tile> tiles_;
};
*/
#include "map.hpp"

//====================
// coord

Coord::Coord(int x, int y) {
    pos_x_ = x;
    pos_y_ = y;
}

void Coord::CoordSet(int pos_x, int pos_y) {
    pos_x_ = pos_x;
    pos_y_ = pos_y;
}

int Coord::CoordGetX() {
    return pos_x_;
}

int Coord::CoordGetY() {
    return pos_y_;
}

//====================
// map

Map::Map(std::vector<Tile> tiles, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            tiles_[Coord(width, height)] = tiles[y * width + x];
            tiles_[Coord(width, height)].SetMap(this); // FIXME it works!?!?!
        }
    }
}

Entity Map::GetEntity(std::vector<int> path) {
}

AbilityResult Map::ApplyAbility(std::vector<int> path_origin, std::vector<int> path_target,
                                AbilityKindEntityActive ability_kind) {
}

bool Map::PushEntity(std::vector<int> path, Entity& entity) {
}
