#include "ability-factory.hpp"
#include "../main-classes/main-classes.hpp"

//====================
// ability factory

Ability AbilityFactory::CreateAbilityDie(size_t hp_max, size_t hp_current) {
    Ability ability_die = Ability(CanDie, {{HpMax, hp_max}, {HpCurrent, hp_current}});

    return ability_die;
}

Ability AbilityFactory::CreateAbilityKick(size_t damage) {
    Ability ability_kick = Ability(CanKick, {{DamageAmount, damage}});

    return ability_kick;
}

Ability AbilityFactory::CreateAbilityPick() {
    Ability ability_pick = Ability(CanPick, {});

    return ability_pick;
}

Ability AbilityFactory::CreateAbilityLoot() {
    Ability ability_pick = Ability(CanLoot, {{SpotToLoot, 0}});

    return ability_pick;
}

Ability AbilityFactory::CreateAbilityBePicked() {
    Ability ability_be_picked = Ability(CanBePicked, {});

    return ability_be_picked;
}

Ability AbilityFactory::CreateAbilityContain(size_t capacity) {
    Ability ability_contain = Ability(CanContain, {{ContainCapacity, capacity}});

    return ability_contain;
}

Ability AbilityFactory::CreateAbilityMove() {
    Ability ability_move = Ability(CanMove, {});

    return ability_move;
}

Ability AbilityFactory::CreateAbilityHack(size_t hack_level) {
    Ability ability_hack = Ability(CanHack, {{HackLevel, hack_level}});

    return ability_hack;
}

Ability AbilityFactory::CreateAbilityBeLocked(size_t lock_level) {
    Ability ability_be_locked = Ability(CanBeLocked, {{LockLevel, lock_level}});

    return ability_be_locked;
}

Ability AbilityFactory::CreateAbilityBeMap(size_t width, size_t height) {
    Ability ability_be_map = Ability(IsMap, {{MapWidth, width}, {MapHeight, height}});
    return ability_be_map;
}
