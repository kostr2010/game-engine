#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>

#include "engine-types.h"
#include "engine-constants.h"

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

    return;
}

int Ability::GetStateValue(AbilityState name) {
    std::cout << "get " << name << std::endl;

    for (auto& key : state_)
        std::cout << key.second << std::endl;

    return state_[name];
}

void Ability::SetStateValue(AbilityState name, int new_value) {
    std::cout << "set " << name << " to " << new_value << std::endl;
    
    state_[name] = new_value;

    return;
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
// entity

Entity::Entity(std::vector<Ability> abilities) {    
    for (const auto& ability : abilities)
        abilities_[ability.kind_] = ability;

    return;
}

void Entity::Apply(AbilityKind kind, Entity& target) {
    if (abilities_.count(kind) != 0)
        dict_ability_dispatcher[kind](*this, target);

    return;
}
    
std::ostream& operator<< (std::ostream& stream, Entity entity) {
    for (const auto& ability : entity.abilities_)
        stream << "AbilityKind - " << ability.first << ", Ability:" << ability.second << std::endl; 

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
    Ability ability_pick = Ability(CanPick, {{/*FIXME what to put here*/}});

    return ability_pick;
}

Ability AbilityFactory::CreateAbilityLoot() {
    Ability ability_pick = Ability(CanLoot, {{SpotToLoot, -1}});

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

Ability CreateAbilityHack(size_t hack_level) {
    Ability ability_hack = Ability(CanHack, {{HackLevel, hack_level}});

    return ability_hack;
}

Ability CreateAbilityBeLocked(size_t lock_level) {
    Ability ability_be_locked = Ability(CanBeLocked, {{LockLevel, lock_level}});

    return ability_be_locked;
}

//====================
// character factory

Entity EntityFactory::CreateWarrior() {
    Ability ability_die     = AbilityFactory::CreateAbilityDie(10, 10);
    Ability ability_kick    = AbilityFactory::CreateAbilityKick(4);
    Ability ability_pick    = AbilityFactory::CreateAbilityPick();
    Ability ability_loot    = AbilityFactory::CreateAbilityLoot();
    Ability ability_contain = AbilityFactory::CreateAbilityContain(10);
    Ability ability_hack    = AbilityFactory::CreateAbilityHack(1);
    Ability ability_move    = AbilityFactory::CreateAbilityMove();

    return Entity({ability_die, 
                   ability_kick, 
                   ability_pick, 
                   ability_loot, 
                   ability_contain,
                   ability_hack,
                   ability_move});
}
/*
Entity EntityFactory::CreateMage() {

}

Entity EntityFactory::CreateCustom() {

}
*/

Entity EntityFactory::CreateChest(size_t init_lock_lvl) {
    Ability ability_conntain  = AbilityFactory::CreateAbilityContain(20);
    Ability ability_die       = AbilityFactory::CreateAbilityDie(100, 100);
    Ability ability_be_locked = AbilityFactory::CreateAbilityBeLocked(init_lock_lvl);

    return Entity({ability_die, ability_conntain});
}

Entity EntityFactory::CreateMimic() {

}

/*
Ability EntityFactory::GetHealthAbility(size_t hp_max, size_t hp_current) {

}

Ability EntityFactory::GetKickAbility(size_t damage) {

}
*/