#pragma once

#include <algorithm>
#include <vector>

#include "../../component/components/container.hpp"
#include "../../property/properties.hpp"
#include "../system.hpp"

class SystemContainer : public System {
public:
  SystemContainer(Monitor* monitor) : System(monitor) {
  }

  void Pick(Entity entity_origin, Entity entity_target) {
    assertm(monitor_->HasComponent<ComponentContainer>(entity_origin),
            "entity origin is not a container");
    assertm(monitor_->HasProperty(entity_target, Pickable), "entity origin has no picking ability");

    ComponentContainer* origin_comp_contain =
        monitor_->GetComponent<ComponentContainer>(entity_origin);

    origin_comp_contain->subentities.push_back(entity_target);
  }

  void Drop(Entity entity_origin, Entity entity_target) {
    assertm(monitor_->HasComponent<ComponentContainer>(entity_origin),
            "entity origin is not a container");
    assertm(monitor_->HasProperty(entity_target, Pickable), "entity origin has no picking ability");

    ComponentContainer* origin_comp_contain =
        monitor_->GetComponent<ComponentContainer>(entity_origin);

    auto position = std::find(origin_comp_contain->subentities.begin(),
                              origin_comp_contain->subentities.end(),
                              entity_target);
    assertm(position != origin_comp_contain->subentities.end(),
            "entity tries to drop an entity it does not have");

    origin_comp_contain->subentities.erase(position);
  }

  void Transfer(Entity entity_from, Entity entity_whom, Entity entity_to) {
    Drop(entity_from, entity_whom);
    Pick(entity_to, entity_whom);
  }
};