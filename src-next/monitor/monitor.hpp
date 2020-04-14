#pragma once

#include <cassert>
#include <vector>

#include "../component/component.hpp"
#include "../entity/entity.hpp"
#include "../system/system.hpp"
#include "../system/systemManager.hpp"
#include "../utils/assembly.hpp"
#include "../utils/log.hpp"

// ====================
// Monitor
// global manager for all managers

class Monitor {
public:
  Monitor() {
    LOG_LVL_MONITOR_INIT();

    component_manager_ = ComponentManager{};
    // TODO add try/catch here
    LOG_LVL_MONITOR("ComponentManager initialized");

    entity_manager_ = EntityManager{};
    // TODO add try/catch here
    LOG_LVL_MONITOR("EntityManager initialized");

    system_manager_ = SystemManager{this};
    // TODO add try/catch here
    LOG_LVL_MONITOR("SystemManager initialized");

    // при попытке вызова конструкторов в ф-ии Init, конструктор пытался сначала вызвать дефолтный
    // к-тор СисМан

    // Init();
  }
  ~Monitor() = default;

  // wrappers for managers, so user has to speak only to monitor instead of directly to each one of
  // the managers

  template <typename Component_t>
  Component RegisterComponent() {
    Component component = component_manager_.RegisterComponent<Component_t>();

    // TODO add try/catch here
    LOG_LVL_MONITOR("component " << typeid(Component_t).name() << " registered with id "
                                 << component);

    return component;
  }

  template <typename Component_t>
  void AttachComponent(Entity entity, Component_t component_new) {
    component_manager_.AttachComponent(entity, component_new);

    Signature signature_prev = entity_manager_.GetSignature(entity);
    Component component      = component_manager_.GetComponentType<Component_t>();

    Signature signature_new = signature_prev.set(component, true);

    UpdateSignature(entity, signature_new);

    // TODO add try/catch here
    LOG_LVL_MONITOR("component " << typeid(Component_t).name() << " aka " << component
                                 << " attached to entity " << entity << ". now it's signature is "
                                 << entity_manager_.GetSignature(entity));
  }

  template <typename Component_t>
  void RemoveComponent(Entity entity) {
    component_manager_.RemoveComponent<Component_t>(entity);

    Signature signature_prev = entity_manager_.GetSignature(entity);
    Component component      = component_manager_.GetComponentType<Component_t>();

    Signature signature_new = signature_prev.set(component, false);

    UpdateSignature(entity, signature_new);

    // TODO add try/catch here
    LOG_LVL_MONITOR("component " << typeid(Component_t).name() << " aka " << component
                                 << " removed from entity " << entity << ". now it's signature is "
                                 << entity_manager_.GetSignature(entity));
  }

  Entity AddEntity() {
    Entity entity_new = entity_manager_.CreateEntity();

    // TODO add try/catch here
    LOG_LVL_MONITOR("new entity with id " << entity_new << " registered");

    return entity_new;
  }

  void RemoveEntity(Entity entity) {
    entity_manager_.RemoveEntity(entity);
    component_manager_.RemoveEntity(entity);
    system_manager_.RemoveEntity(entity);

    // TODO add try/catch here
    LOG_LVL_MONITOR("entity " << entity << "deleted from all managers");
  }

  // !!! it doesn't set, it adds system with given signature
  template <typename System_t>
  void SetSystemSignature(Signature signature) {
    system_manager_.SetSignature<System_t>(signature);

    // TODO add try/catch here
    // LOG_LVL_MONITOR("now ");
  }

  template <typename System_t>
  System* RegisterSystem(std::vector<Component> components) {
    assertm(system_manager_.Contains<System_t>(), "this system has already been registered");

    System* system = system_manager_.RegisterSystem<System_t>();

    // merge all components to one signature
    Signature signature;
    for (auto& component : components) {
      signature.set(component, true);
    }

    // set the system's initial signature
    SetSystemSignature<System_t>(signature);

    // TODO add try/catch here
    LOG_LVL_MONITOR("new system " << typeid(System_t).name() << " registered");

    return system;
  }

  template <typename System_t>
  System_t* GetSystem() {
    return system_manager_.GetSystem<System_t>();
  }

  template <typename Component_t>
  Component_t* GetComponent(Entity entity) {
    return component_manager_.GetComponent<Component_t>(entity);
  }

  bool CheckIfEntityExists(Entity entity) {
    return entity_manager_.CheckIfEntityExists(entity);
  }

  void Print() {
    component_manager_.Print();
  }

private:
  void UpdateSignature(Entity entity, Signature signature) {
    entity_manager_.SetSignature(entity, signature);
    system_manager_.UpdateEntitySignature(entity, signature);

    // TODO add try/catch here
    LOG_LVL_MONITOR("entity's " << entity << " signature updated. now it's signature is "
                                << signature);
  }

  // creates entity, system, component managers
  void Init() {
  }

  ComponentManager component_manager_{};
  EntityManager    entity_manager_{};
  SystemManager    system_manager_{this};
};