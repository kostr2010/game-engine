#pragma once

#include <iostream>

struct ComponentMovement {
  int speed;
};

std::ostream& operator<<(std::ostream& os, ComponentMovement comp_movement) {
  return os << "speed: " << comp_movement.speed << std::endl;
}