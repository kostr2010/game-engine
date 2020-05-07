#pragma once

#include <cassert>
#include <chrono>
#include <thread>
#include <vector>

#include "../component/component.hpp"
#include "../entity/entity.hpp"
#include "../map/map.hpp"

#include "../property/properties.hpp"
#include "../property/property.hpp"

#include "../system/system.hpp"
#include "../system/systemManager.hpp"

#include "../utils/assembly.hpp"
#include "../utils/log.hpp"
#include "../utils/vec2.hpp"

#include <dlfcn.h>

#include "./imonitor.hpp"

// ====================
// Monitor
// global manager for all managers

class Monitor : public IMonitor {
public:
  Monitor();
  ~Monitor() = default;

  // wrappers for managers, so user has to speak only to monitor instead of directly to each one of
  // the managers

  ComponentTypeLocal RegisterComponent(ComponentTypeGlobal comp_type) override {
    // if (component_manager_.Contains<Component_t>())
    //   return component_manager_.GetComponentType<Component_t>();

    ComponentTypeLocal component = component_manager_.RegisterComponent(comp_type);

    // TODO add try/catch here
    LOG_LVL_MONITOR_ROUTINE("component " << comp_type << " registered with id " << component);

    return component;
  }

  void AttachComponent(ComponentTypeGlobal comp_type, void* component, EntityId entity) override {
    component_manager_.AttachComponent(entity, comp_type, component);

    Signature          signature_prev  = entity_manager_.GetSignature(entity);
    ComponentTypeLocal comp_type_local = component_manager_.GetComponentType(comp_type);

    Signature signature_new = signature_prev.set(comp_type_local, true);

    UpdateSignature(entity, signature_new);

    // TODO add try/catch here
    LOG_LVL_MONITOR_ROUTINE("component "
                            << comp_type << " aka " << component << " attached to entity " << entity
                            << ". now it's signature is " << entity_manager_.GetSignature(entity));
  };

  // template <typename Component_t>
  void RemoveComponent(ComponentTypeGlobal comp_type, void* component, EntityId entity) override {
    component_manager_.RemoveComponent(comp_type, entity);

    Signature          signature_prev  = entity_manager_.GetSignature(entity);
    ComponentTypeLocal comp_type_local = component_manager_.GetComponentType(comp_type);

    Signature signature_new = signature_prev.set(comp_type_local, false);

    UpdateSignature(entity, signature_new);

    // TODO add try/catch here
    LOG_LVL_MONITOR_ROUTINE(
        "component " << comp_type << " aka " << comp_type_local << " removed from entity " << entity
                     << ". now it's signature is " << entity_manager_.GetSignature(entity));
  }

  EntityId AddEntity() override {
    EntityId entity_new = entity_manager_.CreateEntity();

    // TODO add try/catch here
    LOG_LVL_MONITOR_ROUTINE("new entity with id " << entity_new << " registered");

    return entity_new;
  }

  void RemoveEntity(EntityId entity) override {
    // std::cout << "  > start removing from entity manager\n";
    entity_manager_.RemoveEntity(entity);
    // std::cout << "  > start removing from component manager\n";
    component_manager_.RemoveEntity(entity);
    // std::cout << "  > start removing from system manager\n";
    system_manager_.RemoveEntity(entity);
    // std::cout << "  > removed from all systems\n";

    // TODO add try/catch here
    LOG_LVL_MONITOR_ROUTINE("entity " << entity << "deleted from all managers");
  }

  System* RegisterSystem(SystemConstructor ctor) override {
    System* system = system_manager_.RegisterSystem(ctor);

    // TODO add try/catch here
    LOG_LVL_MONITOR_ROUTINE("new system " << system->GetMyOwnFuckingShittyId() << " registered");

    return system;
  }

  System* GetSystem(std::string sys_name) override {
    return system_manager_.GetSystem(sys_name);
  }

  template <typename Component_t>
  bool HasComponent(EntityId entity) override {
    return component_manager_.HasComponent<Component_t>(entity);
  }

  template <typename Component_t>
  bool HasNoComponent(EntityId entity) override {
    return !HasComponent<Component_t>(entity);
  }

  template <typename Component_t>
  Component_t* GetComponent(EntityId entity) override {
    return component_manager_.GetComponent<Component_t>(entity);
  }

  void AttachProperty(EntityId entity, PropertyType property) override {
    property_manager_.AttachProperty(entity, property);
  }

  void RemoveProperty(EntityId entity, PropertyType property) override {
    property_manager_.RemoveProperty(entity, property);
  }

  bool HasProperty(EntityId entity, PropertyType property) override {
    return property_manager_.HasProperty(entity, property);
  }

  bool HasNoProperty(EntityId entity, PropertyType property) override {
    return property_manager_.HasNoProperty(entity, property);
  }

  bool CheckIfEntityExists(EntityId entity) override {
    return entity_manager_.CheckIfEntityExists(entity);
  }

  void StartLoop() override {
    std::chrono::steady_clock::time_point begin_prev = std::chrono::steady_clock::now();

    while (true) {
      auto begin = std::chrono::steady_clock::now();
      auto time_delta =
          std::chrono::duration_cast<std::chrono::milliseconds>(begin - begin_prev).count();

      // calling updaters
      system_manager_.Update(time_delta);

      auto end = std::chrono::steady_clock::now();

      // std::cout << "I'm a dwarf and I'm digging the hole" << std::endl;

      const int64_t LOOP_DURATION = 16; // 60fps
      auto          time_elapsed =
          std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
      auto time_to_sleep = LOOP_DURATION - time_elapsed;

      if (time_to_sleep > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep));

      begin_prev = begin;
    }
  }

  System* ImportSystem(SystemName name) override {
    if (system_manager_.Contains(name))
      return system_manager_.GetSystem(name);

    void* handle = ImportDLL(name);

    SystemConstructor ctor = (SystemConstructor)dlsym(handle, "create_object");

    return ctor(this);
  }

private:
  void* ImportDLL(std::string path) override {
    const char* c_path = path.c_str();

    /* on Linux, use "./myclass.so" */
    void* handle = dlopen(c_path, RTLD_LAZY);

    return handle;
  }

  void UpdateSignature(EntityId entity, Signature& signature) override {
    // std::cout << "*\n" << std::endl;
    entity_manager_.SetSignature(entity, signature);
    // std::cout << "*\n" << std::endl;
    system_manager_.UpdateEntitySignature(entity, signature);
    // std::cout << "*\n" << std::endl;

    // TODO add try/catch here
    LOG_LVL_MONITOR_ROUTINE("entity's " << entity << " signature updated. now it's signature is "
                                        << signature);
  }

  PropertyManager  property_manager_{};
  ComponentManager component_manager_{};
  EntityManager    entity_manager_{};
  SystemManager    system_manager_{this};
};