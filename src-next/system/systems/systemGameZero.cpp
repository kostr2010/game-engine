#include "./systemGameZero.hpp"

extern "C" SystemGameZero* create_object(SystemManager* sys_man) {
  return new SystemGameZero{sys_man};
}

extern "C" void destroy_object(SystemGameZero* object) {
  delete object;
}

SystemGameZero::SystemGameZero(SystemManager* sys_man) : System(sys_man) {
}

ResponseCode SystemGameZero::Init() {
  EntityId dummy = system_manager_->entity_manager_.CreateEntity();

  ComponentHealth comp_health{10, 10};
  (system_manager_->component_manager_).AttachComponent("componentHealth", &comp_health, dummy);

  // (SystemHealth*)system_manager_->GetSystem("SystemHealth");
  SystemHealth* sys_health = (SystemHealth*)system_manager_->GetSystem("systemHealth");
  sys_health->ChangeCurrentHp(dummy, -3);

  return ResponseCode::Success;
}

std::vector<ComponentTypeGlobal> SystemGameZero::GetRequiredComponentTypes() {
  // return {"ComponentHealth"};
  return {};
}

std::vector<ComponentTypeGlobal> SystemGameZero::GetDependentComponentTypes() {
  return {};
}

std::vector<SystemName> SystemGameZero::GetDependentSystemNames() {
  return {"systemHealth", "systemKick"};
};

std::string SystemGameZero::GetMyOwnFuckingShittyId() {
  return "systemGameZero";
}