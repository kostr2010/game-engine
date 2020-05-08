#include "./entity.hpp"
#include "../utils/log.hpp"

EntityManager::~EntityManager() = default;

EntityManager::EntityManager() {
  for (int i = MAX_ENTITIES; i >= 0; i--)
    available_ids_.push_back(i);

  LOG_LVL_ENTITY_INIT("../log/entity.log");
  LOG_LVL_ENTITY_ROUTINE("EntityManager initialized");
}

EntityId EntityManager::CreateEntity() {
  auto id = available_ids_.back();
  available_ids_.pop_back();

  LOG_LVL_ENTITY_ROUTINE("entity with id " << id << " created");

  return id;
}

void EntityManager::RemoveEntity(EntityId entity) {
  // std::cout << "    > ent man RemoveEntity " << entity << "\n";

  available_ids_.push_back(entity);
  abilities_signatures_[entity].reset();

  LOG_LVL_ENTITY_ROUTINE("entity with id " << entity << " removed");
}

Signature EntityManager::GetSignature(EntityId entity) {
  return abilities_signatures_[entity];
}

Signature EntityManager::SetSignature(EntityId entity, Signature signature) {
  LOG_LVL_ENTITY_ROUTINE("entity's " << entity << " signature is now set to " << signature);

  return abilities_signatures_[entity] = signature;
}

bool EntityManager::CheckIfEntityExists(EntityId entity_target) {
  return std::find(available_ids_.begin(), available_ids_.end(), entity_target) ==
         available_ids_.end();
}