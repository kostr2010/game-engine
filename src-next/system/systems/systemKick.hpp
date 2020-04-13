#pragma once

#include "../../component/components/kick.hpp"
#include "../system.hpp"
#include "./systemHealth.hpp"

class SystemKick : public System {
public:
  SystemKick(Monitor* monitor) : System(monitor) {
  }

  bool Kick(Entity entity_origin, Entity entity_target) {
    // TODO: assert if kick component exists
    ComponentKick* comp_kick = monitor_->GetComponent<ComponentKick>(entity_origin);

    // TODO: assert if health system exists
    SystemHealth* sys_health = monitor_->GetSystem<SystemHealth>();

    LOG_LVL_SYSTEM("SystemKick",
                   "entity " << entity_origin << " kicks entity " << entity_target << " for "
                             << comp_kick->damage_amount << " points of damage!");

    sys_health->ChangeCurrentHp(entity_target, -1 * comp_kick->damage_amount);

    return true;
  }
};
