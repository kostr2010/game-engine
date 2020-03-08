#pragma once

#include "./entity.hpp"

enum class EventType {
    Death,
    Stun,
};

struct AbilityResult {
    Entity                     entity_before;
    Entity                     entity_after;
    EventType                  event_type;
    std::vector<AbilityResult> sub_results;
};