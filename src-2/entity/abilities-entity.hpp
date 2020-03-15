#pragma once

enum class AbilityKindEntity {
    IsMortal,
    IsContainer,
    IsLockable,
    IsConsumable,
    IsPickable,
};

enum class AbilityKindEntityActive {
    CanMove,
    CanKick,
    CanPick,
    CanLoot,
    CanHack,
    CanConsume,
};

enum class AbilityStateEntity {
    HPMax,
    HPCur,
    Capacity,
    LockLevel,
    //
    //
};

enum class AbilityStateEntityActive {
    Movability,
    DamageKick,
    //
    SpotToLoot,
    HackLevel,
    //
};