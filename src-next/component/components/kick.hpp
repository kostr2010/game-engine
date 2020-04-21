#pragma once

#include <iostream>

struct ComponentKick {
  int damage_amount;

  json Serialize() {
    json j{};

    j["damage_amount"] = this->damage_amount;

    return j;
  }

  static ComponentKick* Deserialize(json j) {
    ComponentKick* comp = new ComponentKick;
    comp->damage_amount = j["damege_amount"].get<int>();
    return comp;
  }
};

std::ostream& operator<<(std::ostream& os, ComponentKick& comp_kick) {
  return os << "dmg: " << comp_kick.damage_amount;
}