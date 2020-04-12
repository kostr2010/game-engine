#pragma once

#include "../../component/components/container.hpp"
#include "../../component/components/pick.hpp"
#include "../system.hpp"

class SystemContainer : public System {
public:
  SystemContainer(Monitor* monitor) : System(monitor) {
  }

  void Pick(Entity entity_origin, Entity entity_target) {
    ComponentPick* target_comp_pick = monitor_->GetComponent<ComponentPick>(entity_target);

    if (!target_comp_pick)
      return;

    ComponentContainer* origin_comp_contain =
        monitor_->GetComponent<ComponentContainer>(entity_origin);
  }

  void Drop(Entity entity);
};