#pragma once

//====================
// ENUMS

enum AbilityKind {
    CanDie,        // is tough. can be damaged or healed
    CanContain,    // may contain something pickable
    CanBePicked,   // may be picked up
    CanMove,       // ability to move to another tile
    CanPick,       // can pick pickable                    | FIXME
    CanLoot,       // can pick subEntities of CanContain   |
    CanKick,       // ability to impact physical damage to another person
    CanHack,       // can unlock CanBeLocked instance
    CanBeLocked,   // can be locked
    IsMap,         // map special ability
    IsTransparent, //
    IsWalkable,    //
};

enum AbilityState {
    DamageAmount,      // amount of damage dealt per kick | FIXME separate damage types / sources
    HpMax,             // max amount of hp entity has
    HpCurrent,         // current amount of hp entity has
    ContainCapacity,   // max capacity of the subentities_ vector
    SpotToLoot,        // index of target.subentities_ vector to loot
    LockLevel,         // lock level [0; n]
                       // warrior uses his weapon to open locked chests at the price of
                       // their durability, rogue uses lockpicks, wizzard uses magic at
                       // the cost of the chance that some loot might be destroyed
    HackLevel,         // if HackLevel >= LockLevel, then can hack
    MapWidth,          //
    MapHeight,         //
    TransparencyLevel, //
    WalkabilityLevel,  //
};

enum EntityKind {
    // heroes
    Warrior,
    // enemies
    Mimic,
    // containers
    Chest,
    // items
    Food,
    // misc
    Map,
    Tile,
};