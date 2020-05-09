#pragma once

#include "../../component/components/componentKick.hpp"
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

class SystemKick : public System {
public:
  SystemKick(SystemManager* sys_man);

  ResponseCode Kick(EntityId entity_origin, EntityId entity_target);

  std::vector<SystemName> GetDependentSystemNames() override;

  std::vector<ComponentTypeGlobal> GetDependentComponentTypes() override;

  std::vector<ComponentTypeGlobal> GetRequiredComponentTypes() override;

  std::string GetMyOwnFuckingShittyId() override;
};
