#pragma once

#include "../../component/components/componentKick.hpp"
#include "../../utils/log.hpp"
#include "../system.hpp"
#include "./systemHealth.hpp"

class SystemKick : public System {
public:
  SystemKick(SystemManager* sys_man);

  ResponseCode Kick(EntityId entity_origin, EntityId entity_target);

  std::vector<SystemName> GetDependentSystemNames() override;

  std::vector<ComponentTypeGlobal> GetDependentComponentTypes() override;

  std::vector<ComponentTypeGlobal> GetRequiredComponentTypes() override;

  std::string GetMyOwnFuckingShittyId() override;
};
