#pragma once

#include <cassert>
#include <vector>

#include "../component/component.hpp"
#include "../entity/entity.hpp"
#include "../system/system.hpp"
#include "../system/systemManager.hpp"
#include "../utils/assembly.hpp"

// ====================
// Monitor
// global manager for all managers

class Monitor {
public:
  Monitor() {
    component_manager_ = ComponentManager{};
    entity_manager_    = EntityManager{};
    system_manager_    = SystemManager{this};

    // при попытке вызова конструкторов в ф-ии Init, конструктор пытался сначала вызвать дефолтный
    // к-тор СисМан

    Init();
  }
  ~Monitor() = default;

  // wrappers for managers, so user has to speak only to monitor instead of directly to each one of
  // the managers

  template <typename Component_t>
  Component RegisterComponent() {
    Component component = component_manager_.RegisterComponent<Component_t>();

    return component;
  }

  template <typename Component_t>
  void AttachComponent(Entity entity, Component_t component_new) {
    component_manager_.AttachComponent(entity, component_new);

    Signature signature_prev = entity_manager_.GetSignature(entity);
    Component component      = component_manager_.GetComponentType<Component_t>();

    Signature signature_new = signature_prev.set(component, true);

    UpdateSignature(entity, signature_new);
  }

  template <typename Component_t>
  void RemoveComponent(Entity entity) {
    component_manager_.RemoveComponent<Component_t>(entity);

    Signature signature_prev = entity_manager_.GetSignature(entity);
    Component component      = component_manager_.GetComponentType<Component_t>();

    Signature signature_new = signature_prev.set(component, false);

    UpdateSignature(entity, signature_new);
  }

  Entity AddEntity() {
    return entity_manager_.CreateEntity();
  }

  void RemoveEntity(Entity entity) {
    entity_manager_.RemoveEntity(entity);
    component_manager_.RemoveEntity(entity);
    system_manager_.RemoveEntity(entity);
  }

  template <typename Component_t>
  void SetSystemSignature(Signature signature) {
    system_manager_.SetSignature<Component_t>(signature);
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
  }

  // creates entity, system, component managers
  void Init() {
  }

  ComponentManager component_manager_{};
  EntityManager    entity_manager_{};
  SystemManager    system_manager_{this};
};