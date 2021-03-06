#include "./systemHealth.hpp"

extern "C" SystemHealth* create_object(SystemManager* sys_man) {
  return new SystemHealth{sys_man};
}

extern "C" void destroy_object(SystemHealth* object) {
  delete object;
}

SystemHealth::SystemHealth(SystemManager* sys_man) : System(sys_man) {
}

ResponseCode SystemHealth::ChangeCurrentHp(EntityId entity, int delta) {
  // REQUIRE_COMPONENT(SystemHealth, ComponentHealth, entity);

  ComponentHealth* comp_health =
      (ComponentHealth*)system_manager_->component_manager_.GetComponent("componentHealth", entity);

  comp_health->hp_cur += delta;

  LOG_LVL_SYSTEM_ROUTINE("systemHealth ",
                         "entity's " << entity << " hp changed from " << comp_health->hp_cur - delta
                                     << " to " << comp_health->hp_cur);

  return ResponseCode::Success;
}

ResponseCode SystemHealth::ChangeMaximumHP(EntityId entity, int delta) {
  // REQUIRE_COMPONENT(SystemHealth, ComponentHealth, entity);

  ComponentHealth* comp_health =
      (ComponentHealth*)system_manager_->component_manager_.GetComponent("ComponentHealth", entity);

  comp_health->hp_max += delta;

  LOG_LVL_SYSTEM_ROUTINE("systemHealth",
                         "entity's " << entity << " max hp was changed from "
                                     << comp_health->hp_max - delta << " to "
                                     << comp_health->hp_max);

  return ResponseCode::Success;
}

std::vector<ComponentTypeGlobal> SystemHealth::GetRequiredComponentTypes() {
  return {"componentHealth"};
}

std::vector<ComponentTypeGlobal> SystemHealth::GetDependentComponentTypes() {
  return {};
}

std::vector<SystemName> SystemHealth::GetDependentSystemNames() {
  return {};
};

std::string SystemHealth::GetMyOwnFuckingShittyId() {
  return "systemHealth";
}