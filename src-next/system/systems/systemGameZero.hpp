#pragma once

#include "../system.hpp"

#include "../../utils/log.hpp"

#include "./systemHealth.hpp"
#include "./systemKick.hpp"

class SystemGameZero : public System {
public:
  SystemGameZero() = delete;

  SystemGameZero(SystemManager* sys_man);

  ResponseCode Init() override;

  std::vector<SystemName> GetDependentSystemNames() override;

  std::vector<ComponentTypeGlobal> GetDependentComponentTypes() override;

  std::vector<ComponentTypeGlobal> GetRequiredComponentTypes() override;

  std::string GetMyOwnFuckingShittyId() override;
};