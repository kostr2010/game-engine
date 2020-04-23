#pragma once

#include "../../component/components/position.hpp"
#include "../../component/components/velocity.hpp"
#include "../system.hpp"

#include <cmath>

class SystemPhysics : public System {
public:
  SystemPhysics(Monitor* monitor) : System(monitor) {
  }

  void update(int delta_time) {
    for (auto& entity : entities_) {
      ComponentVelocity* comp_vel = monitor_->GetComponent<ComponentVelocity>(entity);
      ComponentPosition* comp_pos = monitor_->GetComponent<ComponentPosition>(entity);

      comp_pos->pos.x += comp_vel->velocity.x * delta_time;
      comp_pos->pos.y += comp_vel->velocity.y * delta_time;
    }
  }
};