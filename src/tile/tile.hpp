#pragma once

#include <map>
#include <vector>

#include "../effect/effect.hpp"
#include "../map/map.hpp"

class Tile {
  public:
    Tile()  = default;
    ~Tile() = default;

  private:
    Coord  coordinates_;
    Effect surface_effect_;

    std::vector<EntityPassive> objects_;
    std::vector<EntityActive>  actors_;

    Map* parent_map_;
};