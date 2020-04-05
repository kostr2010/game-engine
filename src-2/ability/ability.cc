#include "ability.hpp"
#include <iostream>

//====================
// Ability

template <class AbilityKind, class AbilityState>

Ability<AbilityKind, AbilityState>::Ability(const AbilityKind&                 kind,
                                            const std::map<AbilityState, int>& init_state) {
    ability_state_ = init_state;
    ability_kind_  = kind;
}

template <class AbilityKind, class AbilityState>

int Ability<AbilityKind, AbilityState>::GetAbilityStateValue(const AbilityState& state) const {
    if (ability_state_.count(state) != 0)
        return ability_state_[state];

    return -1; // FIXME exception
}

template <class AbilityKind, class AbilityState>

void Ability<AbilityKind, AbilityState>::SetAbilityStateValue(const AbilityState& state,
                                                              int                 value_new) {
    if (ability_state_.count(state) != 0)
        ability_state_[state] = value_new;
}

//====================
// AbilityActive

template <class AbilityKindActive, class AbilityStateActive>

AbilityActive<AbilityKindActive, AbilityStateActive>::AbilityActive(
    const AbilityKindActive& kind, const std::map<AbilityStateActive, int>        init_state_active,
    AbilityResultPartial (*dispatcher)(EntityActive& origin, Entity& target), int range)
    : Ability<AbilityKindActive, AbilityStateActive>::Ability(kind, init_state_active) {
    dispatcher_ = dispatcher;
    range_      = range;
}

template <class AbilityKindActive, class AbilityStateActive>

AbilityResult AbilityActive<AbilityKindActive, AbilityStateActive>::Apply(Entity& target) {
    Entity               entity_before  = target;
    AbilityResultPartial result_partial = dispatcher_(this, target);

    return {
        .entity_before = entity_before, .entity_after = target,
        .event_type = result_partial.event_type, .sub_results = result_partial.sub_results
    }
}
