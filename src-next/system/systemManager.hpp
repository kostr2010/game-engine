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

    LOG_LVL_SYSTEM_INIT();
    LOG_LVL_SYSTEM_ROUTINE(SystemManager, "SystemManager initialised");
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

    // TODO add try catch here
    LOG_LVL_SYSTEM_ROUTINE(SystemManager,
                           "new system " << typeid(System_t).name() << " registered");

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

    // TODO add try/catch here
    // LOG_LVL_SYSTEM_ROUTINE(SystemManager, "SystemManager initialised");
  }

  void RemoveEntity(Entity entity) {
    // LOG_LVL_SYSTEM_ROUTINE(SystemManager, "removing entity " << entity);

    for (auto& pair : systems_) {
      auto& system = pair.second;

      system->entities_.erase(entity);

      // LOG_LVL_SYSTEM_ROUTINE(pair.first, "entity " << entity << "removed from system " <<
      // pair.first);
    }

    LOG_LVL_SYSTEM_ROUTINE(SystemManager, "removed entity " << entity);
  }

  void UpdateEntitySignature(Entity entity, Signature entity_signature) {
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

    LOG_LVL_SYSTEM_ROUTINE(SystemManager,
                           "updated entity's " << entity << " signature in every system");
  }

  template <typename System_t>
  bool Contains() const {
    const char* id = typeid(System_t).name();

    return (systems_.find(id) == systems_.end());
  }

  bool EntityBelongsToSystem(Signature signature_entity, Signature signature_system) {
    return (signature_entity & signature_system) == signature_system;
  };
  // private: ?????????
  Monitor*                       monitor_;
  std::map<const char*, System*> systems_{};
  std::map<const char*, Signature>
      system_signatures_{}; // !!!! system_signature_ & entity_signature == system_signature in
                            // order to check if entity has all components needed for this system,
                            // else abort
};
