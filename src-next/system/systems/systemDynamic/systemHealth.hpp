#pragma once

#include "../../../component/components/health.hpp"
// #include "../../monitor/monitor.hpp"
#include "../../system.hpp"

class SystemHealth : public System {
public:
  SystemHealth() = delete;
  // ~SystemHealth() = default;

  SystemHealth(Monitor* monitor);

  virtual ResponseCode ChangeCurrentHp(EntityId entity, int delta);

  virtual ResponseCode ChangeMaximumHP(EntityId entity, int delta);

  virtual std::vector<ComponentType> GetRequiredComponentTypes();

  virtual void RegisterDependencies();
};