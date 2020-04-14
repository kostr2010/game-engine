#pragma once

#include "../../component/components/health.hpp"
// #include "../../monitor/monitor.hpp"
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

    LOG_LVL_SYSTEM(SystemHealth,
                   "entity's " << entity << " hp was changed from " << comp_health->hp_cur - delta
                               << " to " << comp_health->hp_cur << std::endl);

    return true;
  }

  bool ChangeMaximumHP(Entity entity, int delta) {
    // TODO: assert if entity is correct and has given component

    ComponentHealth* comp_health = monitor_->GetComponent<ComponentHealth>(entity);

    comp_health->hp_max += delta;

    LOG_LVL_SYSTEM(SystemHealth,
                   "entity's " << entity << " max hp was changed from "
                               << comp_health->hp_max - delta << " to " << comp_health->hp_max
                               << std::endl);

    return true;
  }
};