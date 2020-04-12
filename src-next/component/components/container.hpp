#pragma once

#include "../../entity/entity.hpp"

#include <iostream>
#include <vector>

struct ComponentContainer {
  std::vector<Entity> subentities_;
};

std::ostream& operator<<(std::ostream& os, ComponentContainer comp_container) {
  os << "subentities: ";
  for (const auto& entity : comp_container.subentities_) {
    os << entity << " ";
  }

  return os << std::endl;
}