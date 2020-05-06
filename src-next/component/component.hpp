#pragma once

#include <array>
#include <cassert>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
// #include <memory>
#include <typeinfo>

#include "../entity/entity.hpp"
#include "../utils/assembly.hpp"
#include "../utils/log.hpp"

#include <stdlib.h>
#include <string.h>

// #include "../../libs/json/json.hpp"
// using json = nlohmann::json;

typedef std::string ComponentTypeGlobal;
typedef int         ComponentTypeLocal;

// struct IComponent {
//   virtual json        Serialize()         = 0;
//   virtual IComponent* Deserialize(json j) = 0;
// };

// ====================
// IComponentPack
// for componentManager to be able to tell abilities that the entity was destroyed

class IComponentPack {
public:
  virtual ~IComponentPack() = default;

  virtual void  RemoveData(EntityId entity)               = 0;
  virtual void  AddData(EntityId entity, void* component) = 0;
  virtual void* GetComponent(EntityId entity)             = 0;
  virtual bool  Contains(EntityId entity) const           = 0;

  // virtual json Serialize() = 0;

  // virtual void Deserialize(json j) = 0;
};

// ====================
// ComponentPack
// for us to be able to store entities that belong to each component

class ComponentPack : public IComponentPack {
public:
  ComponentPack(int comp_id, size_t comp_size) {
    comp_size_ = comp_size;
    comp_id_   = comp_id;

    components_ = calloc(MAX_COMPONENTS, comp_size);
  }

  ~ComponentPack() {
    free(components_);
  }

  void AddData(EntityId entity, void* component) {
    assert(map_entity_index.find(entity) == map_entity_index.end() &&
           "Component added to same entity more than once.");

    // Put new entry at end and update the maps
    size_t newIndex            = components_count_++;
    map_entity_index[entity]   = newIndex;
    map_index_entity[newIndex] = entity;

    CopyComponent(component, GetComponentByIndex(newIndex));
  }

  void RemoveData(EntityId entity) override {
    assert(map_entity_index.find(entity) != map_entity_index.end() &&
           "Removing non-existent component.");

    // Copy element at end into deleted element's place to maintain density
    size_t index_to_remove = map_entity_index[entity];
    size_t index_last      = components_count_ - 1;
    // components_[index_to_remove] = components_[index_last];
    // memcpy(GetComponentByIndex(index_to_remove)

    CopyComponent(index_last, index_to_remove);

    // Update map to point to moved spot
    EntityId last_element_entity          = map_index_entity[index_last];
    map_entity_index[last_element_entity] = index_to_remove;
    map_index_entity[index_to_remove]     = last_element_entity;

    map_entity_index.erase(entity);
    map_index_entity.erase(index_last);

    --components_count_;
  };

  void* GetComponent(EntityId entity) override {
    assert(map_entity_index.find(entity) != map_entity_index.end() &&
           "Retrieving non-existent component.");

    return GetComponentByIndex(map_entity_index[entity]);
  };

  bool Contains(EntityId entity) const override {
    return map_entity_index.find(entity) != map_entity_index.end();
  }

private:
  void* GetComponentByIndex(size_t index) {
    return components_ + index * comp_size_;
  }

  void CopyComponent(void* src, void* dst) {
    memcpy(dst, src, comp_size_);
  }

  void CopyComponent(size_t index_src, size_t index_dst) {
    CopyComponent(GetComponentByIndex(index_src), GetComponentByIndex(index_dst));
  }

  int    comp_id_;
  size_t comp_size_        = 1;
  int    components_count_ = 0;
  void*  components_;

  // Map from an entity ID to an array index.
  std::unordered_map<EntityId, size_t> map_entity_index;

  // Map from an array index to an entity ID.
  std::unordered_map<size_t, EntityId> map_index_entity;
};

// ====================
// ComponentManager
// easy ERROR with all components

class ComponentManager {
public:
  ComponentManager() {
    LOG_LVL_COMPONENT_INIT("../log/component.log");
  }

  ~ComponentManager() {
    for (auto& pair : component_packs_) {
      delete pair.second;
    }
  }

  ComponentTypeLocal RegisterComponent(ComponentTypeGlobal comp_id, size_t comp_size) {
    auto id = comp_id;

    if (component_types_.find(id) != component_types_.end()) {
      LOG_LVL_COMPONENT_ROUTINE(ComponentManager,
                                "component " << id << " is already registered as"
                                             << component_types_[id]);

      return component_types_[id];
    }

    ComponentTypeLocal comp_id_local = next_++;
    component_types_.insert({id, comp_id_local});

    IComponentPack* pack = new ComponentPack{comp_id_local, comp_size};

    component_packs_.insert({id, pack});

    // TODO: add try / catch
    LOG_LVL_COMPONENT_ROUTINE(ComponentManager,
                              "component " << comp_id << " registered as " << comp_id_local);

    return comp_id_local;
  }

  ComponentTypeLocal GetComponentType(ComponentTypeGlobal comp_id) {
    auto id = comp_id;

    // TODO: assert if the component exists

    return component_types_[id];
  }

  void AttachComponent(EntityId entity, ComponentTypeGlobal comp_id, void* component) {
    GetComponentPack(comp_id)->AddData(entity, component);

    // TODO add try / catch
    LOG_LVL_COMPONENT_ROUTINE(ComponentManager,
                              "component " << comp_id << "(" << component << ")"
                                           << " attached to entity " << entity);
  }

  template <typename Component_t>
  void RemoveComponent(EntityId entity) {
    GetComponentPack(comp_id)->RemoveData(entity);

    // TODO add try / catch
    LOG_LVL_COMPONENT_ROUTINE(ComponentManager,
                              "component " << comp_id << "removed from entity " << entity);
  }

  bool HasComponent(EntityId entity, ComponentTypeGlobal comp_id) {
    IComponentPack* comp_pack = GetComponentPack(comp_id);

    assertm(comp_pack != nullptr, "unregistered component");

    return comp_pack->Contains(entity);
  }

  void* GetComponent(EntityId entity, ComponentTypeGlobal comp_id) {
    return GetComponentPack(comp_id)->GetComponent(entity);
  }

  bool Contains(ComponentTypeGlobal comp_id) {
    return component_types_.find(comp_id) != component_types_.end();
  }

  // tell each component_pack that an entity has been destroyed
  // if it has an component for that entity, it will remove it
  void RemoveEntity(EntityId entity) {
    // std::cout << "    > comp man RemoveEntity " << entity << "\n";

    for (auto& pair : component_packs_) {
      // const auto pack_type = pair.first;
      const auto pack = pair.second;

      if (pack->Contains(entity))
        pack->RemoveData(entity);
    }

    // TODO add try / catch
    LOG_LVL_COMPONENT_ROUTINE(ComponentManager,
                              "entity " << entity << " removed from all components");
  }

  void Print() {
    for (auto& pair : component_types_) {
      auto& comp = pair.second;
      std::cout << comp << std::endl;
    }
  }

  // std::vector<ComponentTypeLocal> ComponentTypeGlobalToLocal(std::vector<ComponentTypeGlobal>
  // types_global) {
  //   std::vector<ComponentTypeLocal> types_local;
  //   for (const auto& elem : types_global)
  //     types_local.push_back(component_types_[elem]);

  //   return types_local;
  // }

private:
  // TODO: via Packed Array (the same as with ComponentPack)
  // TODO: use only ComponentTypeLocal
  std::map<ComponentTypeGlobal, ComponentTypeLocal> component_types_{};
  std::map<ComponentTypeGlobal, IComponentPack*>    component_packs_{};

  ComponentTypeLocal next_{};

  IComponentPack* GetComponentPack(ComponentTypeGlobal comp_id) {
    // TODO: check if the component is registeredd

    return component_packs_[comp_id];
  };
};
