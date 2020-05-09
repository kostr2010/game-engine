#pragma once

#include "../../component/components/componentHealth.hpp"
#include "../../utils/log.hpp"
#include "../system.hpp"

class SystemHealth : public System {
public:
  SystemHealth() = delete;

  SystemHealth(SystemManager* sys_man);

  ResponseCode ChangeCurrentHp(EntityId entity, int delta);

  ResponseCode ChangeMaximumHP(EntityId entity, int delta);

  std::vector<SystemName> GetDependentSystemNames() override;

  std::vector<ComponentTypeGlobal> GetDependentComponentTypes() override;

  std::vector<ComponentTypeGlobal> GetRequiredComponentTypes() override;

  std::string GetMyOwnFuckingShittyId() override;
};