#pragma once

#include "../../utils/vec2.hpp"
#include <iostream>

struct ComponentPosition {
  Vec2 pos{};
};

std::ostream& operator<<(std::ostream& os, ComponentPosition pos) {
  return os << "pos: " << pos.pos;
}