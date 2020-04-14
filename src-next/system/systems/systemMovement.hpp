#pragma once
#include "../component/components/movement.hpp"
#include "../component/components/position.hpp"
#include "../system.hpp"

class SystemMovement : public System {
public:
  SystemMovement(Monitor* monitor) : System(monitor) {
  }

  void Move(Entity entity, Vec2 direction) {
    ComponentMovement* comp_move = monitor_->GetComponent<ComponentMovement>(entity);
    ComponentPosition* comp_pos  = monitor_->GetComponent<ComponentPosition>(entity);

    if (comp_move->steps_cur == 0)
      return;

    comp_move->steps_cur--;

    comp_pos->pos += direction;
  }

  void ResetCurrentSteps() {
    for (auto entity : entities_) {
      ComponentMovement* comp_move = monitor_->GetComponent<ComponentMovement>(entity);
      comp_move->steps_cur         = comp_move->steps_max;
    }
  }
};
