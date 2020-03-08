#include <algorithm>
#include "entity.hpp"
#include "../status-effect/status-effect-factory.hpp"

//====================
// Entity

Entity::Entity(
    std::map<AbilityKindEntity, Ability<AbilityKindEntity, AbilityStateEntity>> abilities,
    std::map<EffectKind, int> resistances, std::vector<Entity> subentities, Tile* parent_tile,
    Entity* parent_entity) {
  abilities_     = abilities;
  resistances_   = resistances;
  subentities_   = subentities;
  parent_tile_   = parent_tile;
  parent_entity_ = parent_entity_;
}

bool Entity::operator==(const Entity& right) const {
  return entity_id_ == right.entity_id_;
}

Ability<AbilityKindEntity, AbilityStateEntity>
Entity::AbilitiesGetAbility(const AbilityKindEntity& ability_kind) {
  if (abilities_.count(ability_kind) != 0)
    return abilities_[ability_kind];

  // FIXME throw exception
}

int Entity::AbilitiesCountAbility(const AbilityKindEntity& ability_kind) {
  return abilities_.count(ability_kind);
}

void Entity::SubentitiesAdd(const std::vector<Entity>& items) {
  for (const auto& item : items)
    // FIXME check if full
    subentities_.push_back(item);
}

void Entity::SubentitiesRemove(int index) {
  subentities_.erase(subentities_.begin() + index);
}

int Entity::SubentitiesGetIndex(const Entity& item) const {
  for (int i = 0; i < subentities_.size(); i++) {
    if (subentities_[i] == item)
      return i;
  }

  return -1;
}

void Entity::ResistancesAdd(const std::map<EffectKind, int> resistances) {
  for (const auto& resistance : resistances)
    resistances_[resistance.first] += resistance.second;
}

void Entity::ResistancesRemove(const EffectKind& resistance) {
  resistances_[resistance] = 0;
}

void Entity::EffectsAdd(const EffectKind& effect_kind, int strength, int duration) {
  switch (effect_kind) {
  case EffectKind::Poisoned:
    effects_.push_back(EffectFactory::CreatePoisonedEffect(strength, duration));
    break;
  case EffectKind::Healing:
    effects_.push_back(EffectFactory::CreateHealingEffect(strength, duration));
    break;
  case EffectKind::Slowed:
    effects_.push_back(EffectFactory::CreateSlowedEffect(strength, duration));
    break;
  case EffectKind::Crippled:
    effects_.push_back(EffectFactory::CreateCrippledEffect(strength, duration));
    break;
  case EffectKind::Shocked:
    effects_.push_back(EffectFactory::CreateShockedEffect(strength, duration));
    break;
  case EffectKind::KnockedDown:
    effects_.push_back(EffectFactory::CreateKnockedDownEffect(strength, duration));
    break;
  case EffectKind::Bleeding:
    effects_.push_back(EffectFactory::CreateBleedingEffect(strength, duration));
    break;
  case EffectKind::Neutral:
    return;
  default:
    // FIXME exception
    break;
  }
}

void Entity::EffectsRemove(const EffectKind& effect_kind) { // FIXME test if works
  effects_.erase(
      std::remove_if(effects_.begin(), effects_.end(), [effect_kind](const Effect& effect) -> bool {
        return effect.effect_kind_ == effect_kind;
      }));
}

Tile* Entity::GetParentTile() const {
  return parent_tile_;
}

Entity* Entity::GetParentEntity() const {
  return parent_entity_;
}

//====================
// EntityActive

EntityActive::EntityActive(
    std::map<AbilityKindEntity, Ability<AbilityKindEntity, AbilityStateEntity>> abilities,
    std::map<AbilityKindEntityActive,
             AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>>
                              abilities_active,
    std::map<EffectKind, int> resistances, std::vector<Entity> subentities, Tile* parent_tile,
    Entity* parent_entity)
    : Entity(abilities, resistances, subentities, parent_tile, parent_entity) {

  abilities_active_ = abilities_active;
}

AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>
EntityActive::AbilitiesGetAbilityActive(const AbilityKindEntityActive& ability_kind) {
  if (abilities_active_.count(ability_kind) != 0)
    return abilities_active_[ability_kind];

  // FIXME throw exception
}

int EntityActive::AbilitiesCountAbilityActive(const AbilityKindEntityActive& ability_kind) {
  return abilities_active_.count(ability_kind);
}