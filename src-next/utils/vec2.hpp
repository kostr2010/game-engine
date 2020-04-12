#pragma once

#include <iostream>

class Vec2 {
public:
  Vec2()  = default;
  ~Vec2() = default;
  Vec2(int x, int y) {
    x_ = x;
    y_ = y;
  }

  int x_, y_;
};

void operator+=(Vec2& left, Vec2& right) {
  left.x_ += right.x_;
  left.y_ += left.y_;
}

std::ostream& operator<<(std::ostream& os, Vec2 v) {
  return os << "x: " << v.x_ << " y: " << v.y_ << std::endl;
}