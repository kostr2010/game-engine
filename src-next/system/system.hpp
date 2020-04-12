#pragma once

#include <fstream>
#include <set>

#include "../entity/entity.hpp"
#include "../monitor/monitor.hpp"

// "A system is any functionality that iterates upon a list of entities with a certain signature of
// components."

// mortal and other called abilities will be pulled into the cache for this entity as well as for
// all of the entities near it in the component array, which are likely to be needed with the next
// entity in the list of entities.

// for (auto& entity : entities_) {
//     auto& mortal = GetComponent<Mortal>(entity);
//     mortal.health -= 1;
// }

// ====================
// System
// base class for each system

class Monitor;

class System {
public:
  std::set<Entity> entities_{};

  System(Monitor* monitor) {
    monitor_ = monitor;
  }

protected:
  Monitor* monitor_;
};