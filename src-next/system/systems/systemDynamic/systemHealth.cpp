// #include "../../../component/components/health.hpp"
// // #include "../../monitor/monitor.hpp"
// #include "../../system.hpp"
#include "./systemHealth.hpp"

// SystemHealth::SystemHealth() = delete;
// SystemHealth::~SystemHealth() = default;

extern "C" SystemHealth* create_object(Monitor* monitor) {
  return new SystemHealth{monitor};
}

extern "C" void destroy_object(SystemHealth* object) {
  delete object;
}

SystemHealth::SystemHealth(Monitor* monitor) : System(monitor) {
}

ResponseCode SystemHealth::ChangeCurrentHp(EntityId entity, int delta) {
  REQUIRE_COMPONENT(SystemHealth, ComponentHealth, entity);

  ComponentHealth* comp_health = monitor_->GetComponent<ComponentHealth>(entity);

  comp_health->hp_cur += delta;

  LOG_LVL_SYSTEM_ROUTINE(SystemHealth,
                         "entity's " << entity << " hp changed from " << comp_health->hp_cur - delta
                                     << " to " << comp_health->hp_cur << std::endl);

  return ResponseCode::Success;
}

ResponseCode SystemHealth::ChangeMaximumHP(EntityId entity, int delta) {
  REQUIRE_COMPONENT(SystemHealth, ComponentHealth, entity);

  ComponentHealth* comp_health = monitor_->GetComponent<ComponentHealth>(entity);

  comp_health->hp_max += delta;

  LOG_LVL_SYSTEM_ROUTINE(SystemHealth,
                         "entity's " << entity << " max hp was changed from "
                                     << comp_health->hp_max - delta << " to " << comp_health->hp_max
                                     << std::endl);

  return ResponseCode::Success;
}

std::vector<ComponentTypeGlobal> SystemHealth::GetRequiredComponentTypes() {
  return {monitor_->RegisterComponent<ComponentHealth>()};
}

void SystemHealth::RegisterDependencies() {
}

std::string SystemHealth::GetMyOwnFuckingShittyId() {
  return "SystemHealth";
}