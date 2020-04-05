#pragma once

#include <map>
#include <vector>

#include "../entity/entity.hpp"
#include "./ability-result/ability-result.hpp"

enum class AbilityKindPassive {
    is_mortal,
    is_container,
    is_hackable,
    is_lockpickable,
    is_consumable,
    is_pickable,

};

enum class AbilityKindActive {
    can_move,
    can_kick, // filler ability, remove later
    can_pick,
    can_loot,
    can_hack,
    can_lockpick,
    can_consume,

};

enum class AbilityStatePassive {
    hp_max,
    hp_cur,
    capacity,
    lvl_hack,
    lvl_lock,
    //
    //
};

enum class AbilityStateActive {
    speed,
    dmg_kick,
    //
    spot_to_loot,
    lvl_hacking,
    lvl_lockpicking,
    //
};

class AbilityPassive {
  public:
    AbilityPassive()  = default;
    ~AbilityPassive() = default;

    AbilityPassive(AbilityKindPassive kind, std::map<AbilityStatePassive, int> state);

  private:
    AbilityKindPassive                 kind_;
    std::map<AbilityStatePassive, int> state_;
};

class AbilityActive {
  public:
    AbilityActive()  = default;
    ~AbilityActive() = default;

    AbilityActive(AbilityKindActive kind, std::map<AbilityStateActive, int> state,
                  bool (*dispatcher_passive)(EntityActive& origin, EntityPassive& target),
                  bool (*dispatcher_active)(EntityActive& origin, EntityActive& target));

    AbilityResultPassive Apply(EntityActive& origin, EntityPassive& target);
    AbilityResultActive  Apply(EntityActive& origin, EntityActive& target);

  private:
    AbilityKindActive                 kind_;
    std::map<AbilityStateActive, int> state_;

    AbilityResultPassive (*dispatcher_passive_)(EntityActive& origin, EntityPassive& target);
    AbilityResultActive (*dispatcher_active_)(EntityActive& origin, EntityActive& target);

    int range_;
};