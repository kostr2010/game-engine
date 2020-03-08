#pragma once

enum class AbilityKindEntity {
    IsMortal,
    IsContainer,
    IsLockable,
    IsConsumable,
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
    // FIXME
};

enum class AbilityStateEntityActive {
    Movability,
    DamageKick,
    // FIXME
    SpotToLoot,
    HackLevel,
    // FIXME
};