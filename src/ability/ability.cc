#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

#include "ability.hpp"

//====================
// METHODS IMPLEMENTATION

//====================
// ability

Ability::Ability() {
    return;
}

Ability::Ability(AbilityKind kind, std::map<AbilityState, int> init_state) {
    state_ = init_state;
    kind_  = kind;
}

int Ability::GetStateValue(AbilityState name) {
    return state_[name];
}

void Ability::SetStateValue(AbilityState name, int new_value) {
    state_[name] = new_value;
}

bool operator==(const Ability& left, const Ability& right) {
    return left.state_ == right.state_;
}

std::ostream& operator<<(std::ostream& stream, Ability ability) {
    stream << ability.kind_ << ": ";

    for (const auto& s : ability.state_)
        stream << s.second << " ";

    return stream;
}

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