#pragma once

#include <iostream>

struct ComponentHealth {
  int hp_max, hp_cur;
};

std::ostream& operator<<(std::ostream& os, ComponentHealth comp_health) {
  return os << "max: " << comp_health.hp_max << " cur: " << comp_health.hp_cur << std::endl;
}