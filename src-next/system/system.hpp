#pragma once

#include <fstream>
#include <iostream>
#include <set>

#include "../entity/entity.hpp"
// #include "../monitor/monitor.hpp"
#include "../monitor/imonitor.hpp"
#include "../utils/log.hpp"
#include "../utils/response.hpp"

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
// base class for each system - functionality that operate upon spacific set of entities based on
// their components set

typedef std::string SystemName;

class System {
public:
  std::set<EntityId> entities_{};

  System(IMonitor* monitor) {
    monitor_ = monitor;
  }

  virtual ~System() = default;

  virtual ResponseCode Init() {
    return ResponseCode::Success;
  };

  virtual std::string GetMyOwnFuckingShittyId() = 0;

  virtual std::vector<SystemName> GetDependentSystemNames() = 0; // keys from man just as with c++
  virtual std::vector<ComponentTypeGlobal> GetDependentComponentTypes() = 0;
  virtual std::vector<ComponentTypeGlobal> GetRequiredComponentTypes()  = 0;

  virtual ResponseCode Update(int64_t time_delta) {
    return ResponseCode::Success;
  }

protected:
  IMonitor* monitor_;
};

typedef System* (*SystemConstructor)(IMonitor* monitor);