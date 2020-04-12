#pragma once
#include "../component/components/movement.hpp"
#include "../system.hpp"

class SystemMovement : public System {
public:
  SystemMovement(Monitor* monitor) : System(monitor) {
  }

  void Move(Entity entity, Vec2 direction) {
    ComponentMovement* comp_move = monitor_->GetComponent<ComponentMovement>(entity);
    comp_move->pos += direction;
  }
};
