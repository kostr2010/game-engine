#pragma once

#include "../../entity/entity.hpp"

#include <iostream>
#include <vector>

struct ComponentContainer {
  // FIXME dynamic array / std::array / []check vector size
  std::vector<Entity> subentities;
  int                 capacity;
};

std::ostream& operator<<(std::ostream& os, ComponentContainer comp_container) {
  os << "subentities: ";
  for (const auto& entity : comp_container.subentities) {
    os << entity << " ";
  }

  return os;
}