#pragma once

#include <iostream>

// enum class TerrainType {
//   Metal,
//   Stone,
// };

struct ComponentTerrain {
  int  step_cost;
  bool walkable;
  bool poison;
  bool fire;
  bool bless;
};

std::ostream& operator<<(std::ostream& os, ComponentTerrain terrain) {
  return os << "walkable: " << terrain.walkable << " step_cost: " << terrain.step_cost;
}