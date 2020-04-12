#pragma once

#include <iostream>

struct ComponentVisual {
  char sprite;
};

std::ostream& operator<<(std::ostream& os, ComponentVisual vis_comp) {
  return os << "sprite: " << vis_comp.sprite << std::endl;
}