#include "./ability.hpp"

AbilityPassive::AbilityPassive(AbilityKindPassive kind, std::map<AbilityStatePassive, int> state) {
    kind_  = kind;
    state_ = state;
}

AbilityActive::AbilityActive(AbilityKindActive kind, std::map<AbilityStateActive, int> state,
                             bool (*dispatcher_passive)(EntityActive&  origin,
                                                        EntityPassive& target),
                             bool (*dispatcher_active)(EntityActive& origin,
                                                       EntityActive& target)) {
    kind_               = kind;
    state_              = state;
    dispatcher_passive_ = dispatcher_passive;
    dispatcher_active_  = dispatcher_active;
}

AbilityResultPassive AbilityActive::Apply(EntityActive& origin, EntityPassive& target) {
    EntityPassive target_before = target;

    AbilityResultPassive next_results = dispatcher_passive_(origin, target);

    AbilityResultPassive result{.origin_             = origin,
                                .kind                = this.kind_,
                                .target_before       = target_before,
                                .target_after        = target,
                                .sub_results_passive = next_results};
}

AbilityResultActive AbilityActive::Apply(EntityActive& origin, EntityActive& target) {
    EntityPassive target_before = target;

    dispatcher_active_(origin, target);

    AbilityResultPassive result{.origin        = origin,
                                .kind          = this.kind_,
                                .target_before = target_before,
                                .target_after  = target};
}
}