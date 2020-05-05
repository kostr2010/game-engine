#pragma once

#include <map>
#include <set>
#include <typeinfo>

#include "../entity/entity.hpp"
#include "../utils/assembly.hpp"
// #include "../monitor/monitor."

// ====================
// SystemManager
// registers and manages new systems

class System;

class SystemManager {
public:
  SystemManager(Monitor* monitor) {
    monitor_ = monitor;

    LOG_LVL_SYSTEM_INIT("../log/system.log");
    LOG_LVL_SYSTEM_ROUTINE(SystemManager, "SystemManager initialised");
  }

  ~SystemManager() {
    for (auto& pair : systems_)
      delete (pair.second);
  }

  void SetSystemSignature(std::string sys_name, std::vector<ComponentType> components) {
    // merge all components to one signature
    Signature signature{};
    for (auto& component : components) {
      signature.set(component, true);
    }

    system_signatures_.insert({sys_name, signature});
  }

  System* RegisterSystem(SystemConstructor ctor) {
    System* system = ctor(monitor_);

    std::string sys_name = system->GetMyOwnFuckingShittyId();

    if (systems_.find(sys_name) != systems_.end()) {
      LOG_LVL_SYSTEM_ROUTINE(SystemManager, "system " << sys_name << " already registered");

      // TODO: get rid of dynamic allocation (do static id gathering)
      delete system;

      return systems_[sys_name];
    }

    systems_[sys_name] = system;

    SetSystemSignature(sys_name, system->GetRequiredComponentTypes());
    system->RegisterDependencies();

    auto system_init_code = system->Init();

    assertm(system_init_code == ResponseCode::Success, "System failed to init");

    // TODO: add try catch here
    LOG_LVL_SYSTEM_ROUTINE(SystemManager, "new system " << sys_name << " registered");

    return system;
  }

  System* GetSystem(std::string sys_name) {
    assertm(systems_.find(sys_name) != systems_.end(), "[GetSystem] no system with such name");

    return systems_[sys_name];
  }

  void RemoveEntity(EntityId entity) {
    for (auto& pair : systems_) {
      auto system = pair.second;

      auto it = system->entities_.find(entity);
      if (it == system->entities_.end())
        continue;

      system->entities_.erase(it);
    }

    LOG_LVL_SYSTEM_ROUTINE(SystemManager, "removed entity " << entity);
  }

  void UpdateEntitySignature(EntityId entity, Signature entity_signature) {
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

  bool Contains(System* system) const {
    std::string sys_name = system->GetMyOwnFuckingShittyId();

    return systems_.find(sys_name) != systems_.end();
  }

  bool EntityBelongsToSystem(Signature signature_entity, Signature signature_system) {
    return (signature_entity & signature_system) == signature_system;
  };

  void Update(long time_delta) {
    for (auto& pair : systems_) {
      System* system = pair.second;
      system->Update(time_delta);
    }
  }

private:
  Monitor*                         monitor_;
  std::map<std::string, System*>   systems_{};
  std::map<std::string, Signature> system_signatures_{};
};
