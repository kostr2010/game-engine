#pragma once

#include "../entity/entity.hpp"

#include <array>
#include <list>
#include <map>
#include <typeinfo>

typedef int Component;

// for componentManager to be able to tell abilities that the entity was destroyed
class IComponentPack {
  virtual void AddEntity(Entity entity);
  virtual void RemoveEntity(Entity entity);
};

template <typename Component_t>
class ComponentPack : IComponentPack {
public:
  void AddEntity(Entity entity) override {
    components_[entity] = Component_t{};
  }

  void RemoveEntity(Entity entity) override {
    auto entityIndex = components_.find(entity);

    // TODO: assert for entity index != components_.end()

    components_.erase(entityIndex);
  };

  Component_t& GetComponent(Entity entity) {
    return components_[entity];
  };

  //  RemoveEntity as the wrapper for DeleteEntity - member function without bounds check

private:
  // std::array<Component_t, MAX_ENTITIES> abilities_;
  // entity to index
  // index to entity
  std::map<Entity, Component_t> components_;
};

class ComponentManager {
public:
  ComponentManager()  = default;
  ~ComponentManager() = default;

  template <typename Component_t>
  void RegisterComponent(/* ComponentType type, Component component */) {
    const char* id = typeid(Component_t);
    if (component_packs_.find(id))
      return;

    component_types_.insert({id, next_++});

    component_packs_.insert({id, (ComponentPack<Component_t>()) * });
  }
  template <typename Component_t>
  Component GetComponentType(); // wrapper for private function
  template <typename Component_t>
  void AddComponent(Entity entity, Component_t component);
  template <typename Component_t>
  void RemoveComponent(Entity entity);
  template <typename Component_t>
  Component_t& GetComponent(Entity Entity);

  // int TypeToKey<T>();

  void RemoveEntity(Entity entity); // tell each component_pack that an entity has been destroyed
                                    // if it has an component for that entity, it will remove it

private:
  std::map<const char* /* str(Component) */, Component>       component_types_{};
  std::map<const char* /* str(Component) */, IComponentPack*> component_packs_{};

  Component next_;

  template <typename Component_t>
  ComponentPack<Component_t>* GetComponentPack() {
    return (ComponentPack<Component_t>*)(component_packs_[typeid(Component_t).name()]);
  };

  // std::array<ComponentPackGeneral*, MAX_ENTITIES> packs_;
  // template <typename Component> std::map<ComponentType, ComponentPack<Component>>;
};
