#pragma once

#include <iostream>

struct ComponentKick {
  int damage_amount;
};

std::ostream& operator<<(std::ostream& os, ComponentKick& comp_kick) {
  return os << "dmg: " << comp_kick.damage_amount;
}