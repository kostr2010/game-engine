#pragma once

#include <iostream>

// ====================
// Vec2
// implementation of the simple 2d vector

class Vec2 {
public:
  Vec2()  = default;
  ~Vec2() = default;
  Vec2(int x, int y) {
    x_ = x;
    y_ = y;
  }

  int x_, y_;

  static Vec2 FixedProduct(Vec2 v1, Vec2 v2) {
    return {v1.x_ * v2.x_, v1.y_ * v2.y_};
  }
};

bool operator==(Vec2 left, Vec2 right) {
  return (left.x_ == right.x_) && (left.y_ == right.y_);
}

void operator+=(Vec2& left, Vec2& right) {
  left.x_ += right.x_;
  left.y_ += right.y_;
}

std::ostream& operator<<(std::ostream& os, Vec2 v) {
  return os << "x: " << v.x_ << " y: " << v.y_ << std::endl;
}