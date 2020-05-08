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
#include "./componentInfo.hpp"

#include "../utils/assembly.hpp"
#include "../utils/dll.hpp"
#include "../utils/log.hpp"

#include <string.h>

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
  ComponentPack(ComponentTypeLocal comp_type, size_t comp_size);

  ~ComponentPack();

  void AddData(EntityId entity, void* component);

  void RemoveData(EntityId entity) override;

  void* GetComponent(EntityId entity) override;

  bool Contains(EntityId entity) const override;

private:
  void* GetComponentByIndex(size_t index);

  void CopyComponent(void* src, void* dst);

  void CopyComponent(size_t index_src, size_t index_dst);

  int    comp_type_;
  size_t comp_size_        = 0;
  int    components_count_ = 0;
  void*  components_;

  // Map from an entity ID to an array index.
  std::map<EntityId, size_t> map_entity_index;

  // Map from an array index to an entity ID.
  std::map<size_t, EntityId> map_index_entity;
};

// ====================
// ComponentManager
// easy ERROR with all components

class ComponentManager {
public:
  ComponentManager();

  ~ComponentManager();

  ComponentTypeLocal RegisterComponent(ComponentTypeGlobal comp_type);

  ComponentTypeLocal GetComponentType(ComponentTypeGlobal comp_type);

  void AttachComponent(EntityId entity, ComponentTypeGlobal comp_type, void* component);

  // template <typename Component_t>
  void RemoveComponent(ComponentTypeGlobal comp_type, EntityId entity);

  bool HasComponent(ComponentTypeGlobal comp_type, EntityId entity);

  void* GetComponent(ComponentTypeGlobal comp_type, EntityId entity);

  bool Contains(ComponentTypeGlobal comp_type);

  void RemoveEntity(EntityId entity);

private:
  // TODO: via Packed Array (the same as with ComponentPack)
  // TODO: use only ComponentTypeLocal
  std::map<ComponentTypeGlobal, ComponentTypeLocal> component_types_{};
  std::map<ComponentTypeGlobal, IComponentPack*>    component_packs_{};

  ComponentTypeLocal next_{};

  IComponentPack* GetComponentPack(ComponentTypeGlobal comp_type);
};
