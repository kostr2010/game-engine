#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <map>

//===================
// ENUMS

enum AbilityKind {
    CanDie,         // is tough. can be damaged or healed
    CanContain,     // may contain something pickable    
    CanBePicked,    // may be picked up
    CanMove,        // ability to move to another tile
    CanPick,        // can pick pickable                    | FIXME
    CanLoot,        // can pick subEntities of CanContain   | 
    CanKick,        // ability to impact physical damage to another person
    CanHack,        // can unlock CanBeLocked instance
    CanBeLocked,    // can be locked
};

enum AbilityState {
    DamageAmount,
    HpMax,
    HpCurrent,
    ContainCapacity,
    SpotToLoot,
    Locked,
};

//====================
// CLASSES DECLARATION

class Ability {
public:
    Ability();
    Ability(AbilityKind kind, std::map<AbilityState, double> init_state);

    double GetStateValue(AbilityState name);
    void   SetStateValue(AbilityState name, double new_value);

    friend bool          operator==(const Ability& left, const Ability& right);
    friend std::ostream& operator<<(std::ostream& stream, Ability ability);

    AbilityKind kind_;
private:
    std::map<AbilityState, double> state_;
protected:
};

class Entity {
public:
    Entity(std::vector<Ability> abilities);

    void Apply(AbilityKind kind, Entity& target);

    friend std::ostream& operator<<(std::ostream& stream, Entity entity);

    std::map<AbilityKind, Ability> abilities_;
    std::vector<Entity> subentities_;
private:
protected:
};

class EntityFactory {
public:
    static Entity CreateWarrior();
    static Entity CreateMage();
    static Entity CreateCustom();

    static Entity CreateChest();
    static Entity CreateMimic();
private:
protected:
};

class AbilityFactory {
public:    
    static Ability CreateAbilityDie(size_t hp_max, size_t hp_current);
    static Ability CreateAbilityKick(size_t damage);
    static Ability CreateAbilityPick(); // can pick CanBePicked entities (not subEntites)
    static Ability CreateAbilityLoot(); // int subEntityInstanceToLoot
    static Ability CreateAbilityBePicked(); // no state
    static Ability CreateAbilityContain(size_t capacity);
    static Ability CreateAbilityMove(); // int distance, int (?)fatigure
    static Ability CreateAbilityHack(); // int (?)hackChance
    static Ability CreateAbilityBeLocked(); // bool initialLocked
private:    
protected:
};
