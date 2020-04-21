#pragma once

#include "../../entity/entity.hpp"

#include <iostream>
#include <vector>

struct ComponentContainer {
  // FIXME dynamic array / std::array / []check vector size
  std::vector<Entity> subentities;
  int                 capacity;

  json Serialize() {
    json j{};

    j["subentities"] = this->subentities;
    j["capacity"]    = this->capacity;

    return j;
  }

  static ComponentContainer* Deserialize(json j) {
    ComponentContainer* comp = new ComponentContainer;
    comp->subentities        = j["subentities"].get<std::vector<Entity>>();
    comp->capacity           = j["capacity"].get<int>();

    return comp;
  }
};

std::ostream& operator<<(std::ostream& os, ComponentContainer comp_container) {
  os << "subentities: ";
  for (const auto& entity : comp_container.subentities) {
    os << entity << " ";
  }

  return os;
}