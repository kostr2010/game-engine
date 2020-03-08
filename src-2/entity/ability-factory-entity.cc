#include "ability-factory-entity.hpp"

//====================
// EntityFactory

Ability<AbilityKindEntity, AbilityStateEntity>
AbilityFactoryEntity::CreateAbilityMortal(const int hp_max, const int hp_cur) {
    return Ability<AbilityKindEntity, AbilityStateEntity>(
        AbilityKindEntity::IsMortal,
        {{AbilityStateEntity::HPMax, hp_max}, {AbilityStateEntity::HPCur, hp_cur}});
}

Ability<AbilityKindEntity, AbilityStateEntity>
AbilityFactoryEntity::CreateAbilityContainer(const int capacity) {
    return Ability<AbilityKindEntity, AbilityStateEntity>(
        AbilityKindEntity::IsContainer, {{AbilityStateEntity::Capacity, capacity}});
}

Ability<AbilityKindEntity, AbilityStateEntity>
AbilityFactoryEntity::CreateAbilityLockable(const int lock_level) {
    return Ability<AbilityKindEntity, AbilityStateEntity>(
        AbilityKindEntity::IsLockable, {{AbilityStateEntity::LockLevel, lock_level}});
}

Ability<AbilityKindEntity, AbilityStateEntity> AbilityFactoryEntity::CreateAbilityConsumable() {
    return Ability<AbilityKindEntity, AbilityStateEntity>(AbilityKindEntity::IsConsumable, {});
}

//====================
// EntityFactoryActive

AbilityResultPartial DispatcherMove(EntityActive& origin, Entity& target) {
    // FIXME
    return {.event_type = EventType::Moved, .sub_results = {}};
}

AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>
AbilityFactoryEntityActive::CreateAbilityMove(const int movability) {
    return AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>(
        AbilityKindEntityActive::CanMove,
        {{AbilityStateEntityActive::Movability, movability}},
        DispatcherMove,
        1);
}

AbilityResultPartial DispatcherKick(EntityActive& origin, Entity& target) {
    bool target_can_bleed = target.AbilitiesCountAbility(AbilityKindEntity::IsMortal) != 0;

    if (target_can_bleed) {
        int hp_cur = target.AbilitiesGetAbility(AbilityKindEntity::IsMortal)
                         .GetAbilityStateValue(AbilityStateEntity::HPCur);
        int damage = origin.AbilitiesGetAbilityActive(AbilityKindEntityActive::CanKick)
                         .GetAbilityStateValue(AbilityStateEntityActive::DamageKick);

        target.AbilitiesGetAbility(AbilityKindEntity::IsMortal)
            .SetAbilityStateValue(AbilityStateEntity::HPCur, hp_cur - damage);
    }
    // FIXME exception
    return;
}

AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>
AbilityFactoryEntityActive::CreateAbilityKick(const int damage_base) {
    return AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>(
        AbilityKindEntityActive::CanKick,
        {{AbilityStateEntityActive::DamageKick, damage_base}},
        DispatcherKick,
        1);
}

AbilityResultPartial DispatcherPick(EntityActive& origin, Entity& target) {
    // FIXME
    return;
}

AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>
AbilityFactoryEntityActive::CreateAbilityPick(/* FIXME */) {
    return AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>(
        AbilityKindEntityActive::CanMove, {}, DispatcherPick, 0);
}

AbilityResultPartial DispatcherLoot(EntityActive& origin, Entity& target) {
    // FIXME
    return;
}

AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>
AbilityFactoryEntityActive::CreateAbilityLoot(const int spot_to_loot) {
    return AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>(
        AbilityKindEntityActive::CanLoot,
        {{AbilityStateEntityActive::SpotToLoot, spot_to_loot}},
        DispatcherLoot,
        1);
}

AbilityResultPartial DispatcherHack(EntityActive& origin, Entity& target) {
    // FIXME
    return;
}

AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>
AbilityFactoryEntityActive::CreateAbilityHack(const int hack_level_base) {
    return AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>(
        AbilityKindEntityActive::CanLoot,
        {{AbilityStateEntityActive::HackLevel, hack_level_base}},
        DispatcherHack,
        1);
}

AbilityResultPartial DispatcherConsume(EntityActive& origin, Entity& target) {
    // FIXME
    return;
}

AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>
AbilityFactoryEntityActive::CreateAbilityConsume(/* FIXME */) {
    return AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>(
        AbilityKindEntityActive::CanLoot, {}, DispatcherConsume, 0);
}