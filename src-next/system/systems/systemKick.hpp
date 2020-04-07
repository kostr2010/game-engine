#pragma once

#include "../../component/components/kick.hpp"
#include "../system.hpp"
#include "./systemHealth.hpp"

class SystemKick : public System {
public:
  bool Kick(Entity entity_origin, Entity entity_target) {
    // TODO: assert if kick component exists
    ComponentKick* comp_kick = monitor_->GetComponent<ComponentKick>(entity_origin);

    // TODO: assert if health system exists
    SystemHealth* sys_health = monitor_->GetSystem<SystemHealth>();
    sys_health->ChangeCurrentHp(entity_target, comp_kick->damage_amount);
  }
};