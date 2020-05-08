#pragma once

#include <map>
#include <set>
#include <typeinfo>

#include "../component/component.hpp"
#include "../entity/entity.hpp"

#include "../utils/assembly.hpp"
#include "../utils/dll.hpp"
#include "../utils/log.hpp"

// #include "./system.hpp"

// ====================
// SystemManager
// registers and manages new systems

class System;
class SystemManager;

typedef System* (*SystemConstructor)(SystemManager* sys_man);
typedef std::string SystemName;

class SystemManager {
public:
  SystemManager();

  ~SystemManager();

  void SetSystemSignature(SystemName sys_name, std::vector<ComponentTypeLocal> components);

  System* RegisterSystem(SystemConstructor ctor);

  System* GetSystem(SystemName sys_name);

  System* ImportSystem(SystemName sys_name);

  void RemoveEntity(EntityId entity);

  void UpdateEntitySignature(EntityId entity, Signature entity_signature);

  bool Contains(SystemName name) const;

  bool EntityBelongsToSystem(Signature signature_entity, Signature signature_system);

  void Update(long time_delta);

  ComponentManager component_manager_;
  EntityManager    entity_manager_;

private:
  std::map<std::string, System*>   systems_{};
  std::map<std::string, Signature> system_signatures_{};
};
