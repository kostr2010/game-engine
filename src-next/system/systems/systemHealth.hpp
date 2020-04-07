#pragma once

#include "../../component/components/health.hpp"
#include "../system.hpp"

class SystemHealth : public System {
public:
  SystemHealth()  = default;
  ~SystemHealth() = default;

  SystemHealth(Monitor* monitor) : System(monitor) {
  }

  bool ChangeCurrentHp(Entity entity, int delta) {
    // TODO: assert if entity is correct and has given component

    ComponentHealth* comp_health = monitor_->GetComponent<ComponentHealth>(entity);

    comp_health->hp_cur += delta;

    return true;
  }

  bool ChangeMaximumHP(Entity entity, int delta) {
    // TODO: assert if entity is correct and has given component

    ComponentHealth* comp_health = monitor_->GetComponent<ComponentHealth>(entity);

    comp_health->hp_max += delta;

    return true;
  }
};