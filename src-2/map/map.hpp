#pragma once;

#include <map>
#include "../tile/tile.hpp"
#include "../ability/ability.hpp"

struct Pointer {};

class Coord {
  public:
    Coord(int x, int y);
    Coord();
    ~Coord() = default;

    void CoordSet(int pos_x, int pos_y);
    int  CoordGetX();
    int  CoordGetY();

  private:
    int pos_x_, pos_y_;

  protected:
};

class Map {
  public:
    Map(std::vector<Tile> tiles, int width, int height);
    ~Map() = default;

    Entity        GetEntity(std::vector<int> path);
    AbilityResult ApplyAbility(std::vector<int> path_origin, std::vector<int> path_target,
                               AbilityKindEntityActive ability_kind);

    bool PushEntity(std::vector<int> path, Entity& entity);
    // PushEntityActive ???
  private:
    std::map<Coord, Tile> tiles_;

  protected:
};
