#include "./systemKick.hpp"

extern "C" SystemKick* create_object(SystemManager* sys_man) {
  return new SystemKick{sys_man};
}

extern "C" void destroy_object(SystemKick* object) {
  delete object;
}

SystemKick::SystemKick(SystemManager* sys_man) : System(sys_man) {
}

ResponseCode SystemKick::Kick(EntityId entity_origin, EntityId entity_target) {
  LOG_LVL_SYSTEM_ROUTINE("systemKick",
                         "entity " << entity_origin << " attempts to kick " << entity_target);

  //   REQUIRE_COMPONENT(SystemKick, ComponentKick, entity_origin);
  //   REQUIRE_COMPONENT(SystemKick, ComponentHealth, entity_target);

  ComponentKick* comp_kick = (ComponentKick*)system_manager_->component_manager_.GetComponent(
      "componentKick", entity_origin);

  SystemHealth* sys_health = (SystemHealth*)system_manager_->GetSystem("systemHealth");

  LOG_LVL_SYSTEM_ROUTINE("systemKick",
                         "entity " << entity_origin << " kicks entity " << entity_target << " for "
                                   << comp_kick->dmg << " points of damage!");

  sys_health->ChangeCurrentHp(entity_target, -1 * comp_kick->dmg);

  return ResponseCode::Success;
}

std::vector<SystemName> SystemKick::GetDependentSystemNames() {
  return {"systemHealth"};
}

std::vector<ComponentTypeGlobal> SystemKick::GetDependentComponentTypes() {
  return {};
}

std::vector<ComponentTypeGlobal> SystemKick::GetRequiredComponentTypes() {
  return {"componentKick"};
}

std::string SystemKick::GetMyOwnFuckingShittyId() {
  return "systemKick";
}