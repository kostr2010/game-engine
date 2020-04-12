#include <map>
#include <set>
#include <typeinfo>

#include "./system.hpp"
#include "./systemManager.hpp"

// "A system is any functionality that iterates upon a list of entities with a certain signature of
// components."

// mortal and other called abilities will be pulled into the cache for this entity as well as for
// all of the entities near it in the component array, which are likely to be needed with the next
// entity in the list of entities.

// for (auto& entity : entities_) {
//     auto& mortal = GetComponent<Mortal>(entity);
//     mortal.health -= 1;
// }

// ====================
// System
// base class for each system

// ====================
// SystemManager
// registers new systems

SystemManager::SystemManager() = default;

SystemManager::~SystemManager() {
  for (auto& pair : systems_)
    delete (pair.second);
}

template <typename System_t>
System_t* SystemManager::RegisterSystem() {
  const char* type_name = typeid(System_t).name();

  System_t* system = new System_t{};

  systems_[type_name] = system;

  return system;
}

template <typename System_t>
System_t* SystemManager::GetSystem() {
  const char* type_name = typeid(System_t).name();

  // TODO: assert that the system exists

  return systems_[type_name];
}

template <typename System_t>
void SystemManager::SetSignature(Signature signature) {
  const char* typeName = typeid(System_t).name();

  system_signatures_.insert({typeName, signature});
}

void SystemManager::RemoveEntity(Entity entity) {
  for (auto& pair : systems_) {
    auto& system = pair.second;

    system->entities_.erase(entity);
  }
}

void SystemManager::UpdateEntitySignature(Entity entity, Signature entity_signature) {
  for (auto& pair : systems_) {
    auto& system_type      = pair.first;
    auto& system           = pair.second;
    auto& system_signature = system_signatures_[system_type];

    if (EntityBelongsToSystem(entity_signature, system_signature))
      system->entities_.insert(entity);
    else
      system->entities_.erase(entity);
  }
}

template <typename System_t>
bool SystemManager::Contains() const {
  const char* id = typeid(System_t).name();

  return (systems_.find(id) == systems_.end());
}

bool SystemManager::EntityBelongsToSystem(Signature signature_entity, Signature signature_system) {
  return (signature_entity & signature_system) == signature_system;
};