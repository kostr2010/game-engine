#pragma once
#include "../../component/components/movement.hpp"
#include "../../component/components/position.hpp"
#include "../system.hpp"

class SystemMovement : public System {
public:
  SystemMovement(Monitor* monitor) : System(monitor) {
  }

  ResponseCode Move(Entity entity, Vec2 direction) {
    REQUIRE_COMPONENT(SystemMovement, ComponentMovement, entity);
    REQUIRE_COMPONENT(SystemMovement, ComponentPosition, entity);

    ComponentMovement* comp_move = monitor_->GetComponent<ComponentMovement>(entity);
    ComponentPosition* comp_pos  = monitor_->GetComponent<ComponentPosition>(entity);

    if (comp_move->steps_cur == 0)
      return ResponseCode::Restricted;

    comp_move->steps_cur--;

    // TODO check if direction is valid

    comp_pos->pos += direction;
    return ResponseCode::Success;
  }

  ResponseCode ResetCurrentSteps() {
    for (auto entity : entities_) {
      ComponentMovement* comp_move = monitor_->GetComponent<ComponentMovement>(entity);
      comp_move->steps_cur         = comp_move->steps_max;
    }

    return ResponseCode::Success;
  }
};
