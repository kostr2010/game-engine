#pragma once

#include <map>
#include <set>
#include <typeinfo>

#include "../entity/entity.hpp"
// #include "./system.hpp"

// "A system is any functionality that iterates upon a list of entities with a certain signature of
// components."

// mortal and other called abilities will be pulled into the cache for this entity as well as for
// all of the entities near it in the component array, which are likely to be needed with the next
// entity in the list of entities.

// for (auto& entity : entities_) {
//     auto& mortal = GetComponent<Mortal>(entity);
//     mortal.health -= 1;
// }

// ====================
// System
// base class for each system

// ====================
// SystemManager
// registers new systems

class System;

class SystemManager {
public:
  SystemManager();
  ~SystemManager();

  template <typename System_t>
  System_t* RegisterSystem();

  template <typename System_t>
  System_t* GetSystem();

  template <typename System_t>
  void SetSignature(Signature signature);

  void RemoveEntity(Entity entity);

  void UpdateEntitySignature(Entity entity, Signature entity_signature);

  template <typename System_t>
  bool Contains() const;

  bool EntityBelongsToSystem(Signature signature_entity, Signature signature_system);

  std::map<const char*, System*> systems_{};
  std::map<const char*, Signature>
      system_signatures_{}; // !!!! system_signature_ & entity_signature == system_signature in
                            // order to check if entity has all components needed for this system,
                            // else abort
};
