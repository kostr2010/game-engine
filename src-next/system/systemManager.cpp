#include "./systemManager.hpp"
#include "./system.hpp"

SystemManager::SystemManager() {
  component_manager_ = ComponentManager{};
  // TODO add try/catch here

  entity_manager_ = EntityManager{};
  // TODO add try/catch here

  LOG_LVL_SYSTEM_INIT("../log/system.log");
  LOG_LVL_SYSTEM_ROUTINE("SystemManager", "SystemManager initialised");
}

SystemManager::~SystemManager() {
  for (auto& pair : systems_)
    delete (pair.second);
}

void SystemManager::SetSystemSignature(std::string                     sys_name,
                                       std::vector<ComponentTypeLocal> components) {
  // merge all components to one signature
  Signature signature{};
  for (auto& component : components) {
    signature.set(component, true);
  }

  system_signatures_.insert({sys_name, signature});
}

System* SystemManager::RegisterSystem(SystemConstructor ctor) {
  System* system = ctor(this);

  std::string sys_name = system->GetMyOwnFuckingShittyId();

  if (systems_.find(sys_name) != systems_.end()) {
    LOG_LVL_SYSTEM_ROUTINE("SystemManager",
                           "system " << sys_name << " has already been registered");

    // TODO: get rid of dynamic allocation (do static id gathering)
    delete system;

    return systems_[sys_name];
  }

  systems_[sys_name] = system;

  // registering required components
  auto required_component_types = system->GetRequiredComponentTypes();

  std::vector<ComponentTypeLocal> types_local;
  for (const auto& type : required_component_types)
    types_local.push_back(component_manager_.RegisterComponent(type));

  SetSystemSignature(sys_name, types_local);

  // registering dependencies
  auto dependent_component_types = system->GetDependentComponentTypes();

  for (const auto& type : dependent_component_types)
    component_manager_.RegisterComponent(type);

  auto dependent_system_names = system->GetDependentSystemNames();
  for (const auto& name : dependent_system_names)
    ImportSystem(name);

  auto system_init_code = system->Init();
  assertm(system_init_code == ResponseCode::Success, "[RegisterSystem] System failed to init");

  // TODO: add try catch here
  LOG_LVL_SYSTEM_ROUTINE("SystemManager", "new system " << sys_name << " registered");

  return system;
}

System* SystemManager::GetSystem(std::string sys_name) {
  assertm(systems_.find(sys_name) != systems_.end(), "[GetSystem] no system with such name");

  return systems_[sys_name];
}

System* SystemManager::ImportSystem(std::string sys_name) {
  if (Contains(sys_name))
    return GetSystem(sys_name);

  std::cout << "importing dll" << std::endl;
  void* handle = ImportDLL(sys_name);
  std::cout << "dll imported" << std::endl;

  std::cout << "handle: " << handle << std::endl;

  SystemConstructor ctor = (SystemConstructor)dlsym(handle, "create_object");

  System* system = RegisterSystem(ctor);

  std::cout << "create_object achieved " << ctor << std::endl;

  return system;
}

void SystemManager::RemoveEntity(EntityId entity) {
  for (auto& pair : systems_) {
    auto system = pair.second;

    auto it = system->entities_.find(entity);
    if (it == system->entities_.end())
      continue;

    system->entities_.erase(it);
  }

  component_manager_.RemoveEntity(entity);
  entity_manager_.RemoveEntity(entity);

  LOG_LVL_SYSTEM_ROUTINE("SystemManager", "removed entity " << entity);
}

void SystemManager::UpdateEntitySignature(EntityId entity, Signature entity_signature) {
  // LOG_LVL_SYSTEM_ROUTINE(SystemManager, "updating entity's " << entity << " signature");

  for (auto& pair : systems_) {
    auto& system_type      = pair.first;
    auto& system           = pair.second;
    auto& system_signature = system_signatures_[system_type];

    if (EntityBelongsToSystem(entity_signature, system_signature)) {
      system->entities_.insert(entity);
      // LOG_LVL_SYSTEM_ROUTINE(system_type, "entity " << entity << " added to system " <<
      // system_type);
    } else {
      // LOG_LVL_SYSTEM_ROUTINE(system_type, "entity " << entity << " removed from system " <<
      // system_type);
      system->entities_.erase(entity);
    }
  }

  LOG_LVL_SYSTEM_ROUTINE("SystemManager",
                         "updated entity's " << entity << " signature in every system");
}

bool SystemManager::Contains(SystemName name) const {
  return systems_.find(name) != systems_.end();
}

bool SystemManager::EntityBelongsToSystem(Signature signature_entity, Signature signature_system) {
  return (signature_entity & signature_system) == signature_system;
};

void SystemManager::Update(long time_delta) {
  for (auto& pair : systems_) {
    System* system = pair.second;
    system->Update(time_delta);
  }
}