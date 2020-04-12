#pragma once

#include <iostream>

struct ComponentPick {
  bool is_pickable_;
  bool can_pick_;
};

std::ostream& operator<<(std::ostream& os, ComponentPick comp_container) {
  return os << "pickable (y/n): " << comp_container.is_pickable_ << std::endl;
}