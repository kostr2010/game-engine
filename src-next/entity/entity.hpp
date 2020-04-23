#pragma once

#include <bitset>
#include <set>

const int MAX_ENTITIES   = 128;
const int MAX_COMPONENTS = 32;

// bitmap to keep track of assigned components to specific entities
typedef std::bitset<MAX_COMPONENTS> Signature;

// Entity - just numeric Id
typedef int Entity;

// ====================
// EntityManager
// keeps track of entities and their components(via signatures)

class EntityManager {
public:
  // EntityManager()  = default;
  ~EntityManager() = default;

  EntityManager() {
    for (int i = 0; i < MAX_COMPONENTS; i++)
      available_ids_.insert(i);
  }

  Entity CreateEntity() {
    auto id = available_ids_.begin();
    available_ids_.erase(id);

    return *id;
  }

  void RemoveEntity(Entity entity) {
    available_ids_.insert(entity);
    abilities_signatures_[entity].reset();
  }

  Signature GetSignature(Entity entity) {
    return abilities_signatures_[entity];
  }

  Signature SetSignature(Entity entity, Signature signature) {
    return abilities_signatures_[entity] = signature;
  }

  bool CheckIfEntityExists(Entity entity_target) {
    return available_ids_.find(entity_target) == available_ids_.end();
  }

private:
  std::array<Signature, MAX_ENTITIES>
                   abilities_signatures_{}; // shows whenever an component is present for an entity // list!!!!
  std::set<Entity> available_ids_{}; // TODO: replace "set" with smth better
  int              entities_alive_;
};
