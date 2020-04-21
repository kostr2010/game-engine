#pragma once

#include "../component.hpp"
#include <iostream>

struct ComponentHealth {
  int hp_max, hp_cur;

  json Serialize() {
    json j{};

    j["hp_max"] = this->hp_max;
    j["hp_cur"] = this->hp_cur;

    return j;
  }

  static ComponentHealth* Deserialize(json j) {
    ComponentHealth* comp = new ComponentHealth;
    comp->hp_max          = j["hp_max"].get<int>();
    comp->hp_cur          = j["hp_cur"].get<int>();

    return comp;
  }
};

std::ostream& operator<<(std::ostream& os, ComponentHealth comp_health) {
  return os << "max: " << comp_health.hp_max << " cur: " << comp_health.hp_cur;
}