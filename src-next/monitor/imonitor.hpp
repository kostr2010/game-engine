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

#include "../utils/assembly.hpp"
#include "../utils/log.hpp"
#include "../utils/vec2.hpp"

#include <dlfcn.h>

// ====================
// Monitor
// global manager for all managers

class IMonitor {
public:
  IMonitor();
  ~IMonitor() = default;

  // wrappers for managers, so user has to speak only to monitor instead of directly to each one of
  // the managers

  virtual ComponentTypeLocal RegisterComponent(ComponentTypeGlobal comp_type);

  virtual void AttachComponent(ComponentTypeGlobal comp_type, void* component_new, EntityId entity);

  virtual void RemoveComponent(ComponentTypeGlobal comp_type, void* component, EntityId entity);

  virtual EntityId AddEntity();

  virtual void RemoveEntity(EntityId entity);

  virtual System* RegisterSystem(SystemConstructor ctor);

  virtual System* GetSystem(std::string sys_name);

  virtual bool HasComponent(EntityId entity);

  virtual bool HasNoComponent(EntityId entity);

  virtual void* GetComponent(EntityId entity);

  virtual void AttachProperty(EntityId entity, PropertyType property);

  virtual void RemoveProperty(EntityId entity, PropertyType property);

  virtual bool HasProperty(EntityId entity, PropertyType property);

  virtual bool HasNoProperty(EntityId entity, PropertyType property);

  virtual bool CheckIfEntityExists(EntityId entity);

  virtual void StartLoop();

  virtual System* ImportSystem(SystemName name);

private:
  virtual void* ImportDLL(std::string path);

  virtual void UpdateSignature(EntityId entity, Signature& signature);
};