#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <set>
#include <vector>

const int MAX_ENTITIES   = 128;
const int MAX_COMPONENTS = 32;

// bitmap to keep track of assigned components to specific entities
typedef std::bitset<MAX_COMPONENTS> Signature;

// EntityId - just numeric Id
typedef int EntityId;

// ====================
// EntityManager
// keeps track of entities and their components(via signatures)

class EntityManager {
public:
  // EntityManager()  = default;
  ~EntityManager();

  EntityManager();

  EntityId CreateEntity();

  void RemoveEntity(EntityId entity);

  Signature GetSignature(EntityId entity);

  Signature SetSignature(EntityId entity, Signature signature);

  bool CheckIfEntityExists(EntityId entity_target);

private:
  std::array<Signature, MAX_ENTITIES>
                        abilities_signatures_{}; // shows whenever an component is present for an entity // list!!!!
  std::vector<EntityId> available_ids_{}; // TODO: replace "set" with smth better
  int                   entities_alive_;
};
