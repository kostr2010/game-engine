#pragma once

#include "../entity/entity.hpp"
#include <map>

//====================
// AbilityResult

enum class EventType {
    Died,
    Stunned,
    Moved,
    Damaged,
};

struct AbilityResultPartial {
    EventType                  event_type;
    std::vector<AbilityResult> sub_results;
};

struct AbilityResult : AbilityResultPartial {
    Entity entity_before;
    Entity entity_after;
};

//====================
// Ability

template <class AbilityKind, class AbilityState>

class Ability {
  public:
    Ability(const AbilityKind& kind, const std::map<AbilityState, int>& init_state);
    ~Ability() = default;

    int  GetAbilityStateValue(const AbilityState& state) const;
    void SetAbilityStateValue(const AbilityState& state, int value_new);

    std::map<AbilityState, int> ability_state_;
    AbilityKind                 ability_kind_;

  private:
  protected:
};

//====================
// AbilityActive

template <class AbilityKindActive, class AbilityStateActive>

class AbilityActive : public Ability<AbilityKindActive, AbilityStateActive> {
  public:
    AbilityActive(const AbilityKindActive&                kind,
                  const std::map<AbilityStateActive, int> init_state_active,
                  AbilityResultPartial (*dispatcher)(EntityActive& origin, Entity& target),
                  int range);
    ~AbilityActive() = default;

    AbilityResult Apply(Entity& target);

  private:
    AbilityResultPartial (*dispatcher_)(Entity& origin, Entity& target);
    int range_;

  protected:
};
