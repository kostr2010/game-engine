#pragma once

#include <iostream>

struct ComponentMovement {
  int steps_max;
  int steps_cur;
};

std::ostream& operator<<(std::ostream& os, ComponentMovement comp_movement) {
  return os << "steps_max: " << comp_movement.steps_max << "steps_cur: " << comp_movement.steps_cur
            << std::endl;
}