#pragma once

#include <array>
#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <typeinfo>

#include "../entity/entity.hpp"
#include "../utils/assembly.hpp"

typedef int Component;

// ====================
// IComponentPack
// for componentManager to be able to tell abilities that the entity was destroyed

class IComponentPack {
public:
  virtual void RemoveEntity(Entity entity) = 0;

  virtual bool Contains(Entity entity) const = 0;
};

// ====================
// ComponentPack
// for us to be able to store entities that belong to each component

template <typename Component_t>
class ComponentPack : public IComponentPack {
public:
  // ComponentPack()  = default;
  // ~ComponentPack() = default;

  void AddEntity(Entity entity, Component_t component) {
    components_[entity] = component;
  }

  void RemoveEntity(Entity entity) override {
    auto entity_index = components_.find(entity);

    assertm(entity_index == components_.end(), "entity not found");

    components_.erase(entity_index);
  };

  Component_t* GetComponent(Entity entity) {
    return &(components_[entity]);
  };

  bool Contains(Entity entity) const override {
    return components_.find(entity) != components_.end();
  }

private:
  // std::array<Component_t, MAX_ENTITIES> abilities_;
  // entity to index
  // index to entity
  std::map<Entity, Component_t> components_; // TODO: replace with Packed Array
};

// ====================
// ComponentManager
// easy interaction with all components

class ComponentManager {
public:
  ComponentManager()  = default;
  ~ComponentManager() = default;

  template <typename Component_t>
  Component RegisterComponent() {
    auto id = GetComponentId<Component_t>();

    assertm(component_packs_.find(id) == component_packs_.end(),
            "the component has already been registered");

    Component comp_id = next_++;
    component_types_.insert({id, comp_id});

    // mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
    // std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};

    auto pack = std::make_shared<ComponentPack<Component_t>>();

    // component_packs_.insert({id, std::static_pointer_cast<IComponentPack>(pack)});
    component_packs_.insert({id, pack});

    return comp_id;
  }

  template <typename Component_t>
  Component GetComponentType() { // wrapper for private function
    auto id = GetComponentId<Component_t>();

    // TODO: assert if the component exists

    return component_types_[id];
  }

  template <typename Component_t>
  void AttachComponent(Entity entity, Component_t component) {
    GetComponentPack<Component_t>()->AddEntity(entity, component);
  }

  template <typename Component_t>
  void RemoveComponent(Entity entity) {
    GetComponentPack<Component_t>()->RemoveEntity(entity);
  }

  template <typename Component_t>
  Component_t* GetComponent(Entity entity) {
    return GetComponentPack<Component_t>()->GetComponent(entity);
  }

  // tell each component_pack that an entity has been destroyed
  // if it has an component for that entity, it will remove it
  void RemoveEntity(Entity entity) {
    for (auto& pair : component_packs_) {
      // const auto pack_type = pair.first;
      const auto pack = pair.second;

      if (pack->Contains(entity))
        pack->RemoveEntity(entity);
    }
  }

  void Print() {
    for (auto& pair : component_types_) {
      auto& comp = pair.second;
      std::cout << comp << std::endl;
    }
  }

private:
  std::map<const char*, Component>                       component_types_{};
  std::map<const char*, std::shared_ptr<IComponentPack>> component_packs_{};

  Component next_{};

  template <typename Component_t>
  inline const char* GetComponentId() {
    return typeid(Component_t).name();
  }

  template <typename Component_t>
  std::shared_ptr<ComponentPack<Component_t>> GetComponentPack() {
    // TODO: check if the component is registeredd

    return std::static_pointer_cast<ComponentPack<Component_t>>(
        component_packs_[GetComponentId<Component_t>()]);
  };
};