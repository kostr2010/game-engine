#pragma once

class Vector2 {
public:
  Vector2()  = default;
  ~Vector2() = default;
  Vector2(int x, int y) {
    x_ = x;
    y_ = y;
  }

private:
  int x_, y_;
};

struct ComponentMovement {
  Vector2 vec{};
  int     speed;
};