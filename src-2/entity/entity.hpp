#pragma once

#include "../ability/ability.hpp"
#include "abilities-entity.hpp"
#include "../tile/tile.hpp"
#include "../status-effect/status-effect.hpp"
#include <vector>
#include <map>

class Entity {
  public:
    Entity(std::map<AbilityKindEntity, Ability<AbilityKindEntity, AbilityStateEntity>> abilities,
           std::map<EffectKind, int> resistances, std::vector<Entity> subentities,
           Tile* parent_tile, Entity* parent_entity);
    ~Entity() = default;

    bool operator==(const Entity& right) const;

    Ability<AbilityKindEntity, AbilityStateEntity>
        AbilitiesGetAbility(const AbilityKindEntity& ability_kind);
    int AbilitiesCountAbility(const AbilityKindEntity& ability_kind);

    void SubentitiesAdd(const std::vector<Entity>& items);
    void SubentitiesRemove(int index);
    int  SubentitiesGetIndex(const Entity& item) const;

    void ResistancesAdd(const std::map<EffectKind, int> resistances);
    void ResistancesRemove(const EffectKind& resistance);

    void EffectsAdd(const EffectKind& effect_kind, int strength, int duration);
    void EffectsRemove(const EffectKind& effect_kind);

    Tile*   GetParentTile() const;
    Entity* GetParentEntity() const;

    int entity_id_;

  private:
  protected:
    std::map<AbilityKindEntity, Ability<AbilityKindEntity, AbilityStateEntity>> abilities_;

    std::vector<Effect>       effects_;     // vector of effects, affecting this entity.
    std::map<EffectKind, int> resistances_; // contains resistance (0 - 100) for an active ability.
                                            // if not in the map, resistance is 0
    std::vector<Entity> subentities_;       // children-entities, can't contain EntityActive
    Tile*               parent_tile_;       // pointer to the parent tile. always non-null
    Entity* parent_entity_; // pointer to the entity-parent. always null for EntityActive
};

class EntityActive : public Entity {
  public:
    EntityActive(
        std::map<AbilityKindEntity, Ability<AbilityKindEntity, AbilityStateEntity>> abilities,
        std::map<AbilityKindEntityActive,
                 AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>>
                                  abilities_active,
        std::map<EffectKind, int> resistances, std::vector<Entity> subentities, Tile* parent_tile,
        Entity* parent_entity);
    ~EntityActive() = default;

    AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>
        AbilitiesGetAbilityActive(const AbilityKindEntityActive& ability_kind);
    int AbilitiesCountAbilityActive(const AbilityKindEntityActive& ability_kind);

  private:
    std::map<AbilityKindEntityActive,
             AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>>
        abilities_active_;

  protected:
};
