#pragma once

#include <map>
#include <set>
#include <typeinfo>

#include "../entity/entity.hpp"

// ====================
// SystemManager
// registers and manages new systems

class System;

class SystemManager {
public:
  SystemManager(Monitor* monitor) {
    monitor_ = monitor;
  }

  ~SystemManager() {
    for (auto& pair : systems_)
      delete (pair.second);
  }

  template <typename System_t>
  System_t* RegisterSystem() {
    const char* type_name = typeid(System_t).name();

    System_t* system = new System_t{monitor_};

    systems_[type_name] = system;

    return system;
  }

  template <typename System_t>
  System_t* GetSystem() {
    const char* type_name = typeid(System_t).name();

    // TODO: assert that the system exists

    return (System_t*)systems_[type_name];
  }

  template <typename System_t>
  void SetSignature(Signature signature) {
    const char* typeName = typeid(System_t).name();

    system_signatures_.insert({typeName, signature});
  }

  void RemoveEntity(Entity entity) {
    for (auto& pair : systems_) {
      auto& system = pair.second;

      system->entities_.erase(entity);
    }
  }

  void UpdateEntitySignature(Entity entity, Signature entity_signature) {
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
  bool Contains() const {
    const char* id = typeid(System_t).name();

    return (systems_.find(id) == systems_.end());
  }

  bool EntityBelongsToSystem(Signature signature_entity, Signature signature_system) {
    return (signature_entity & signature_system) == signature_system;
  };

  Monitor*                       monitor_;
  std::map<const char*, System*> systems_{};
  std::map<const char*, Signature>
      system_signatures_{}; // !!!! system_signature_ & entity_signature == system_signature in
                            // order to check if entity has all components needed for this system,
                            // else abort
};