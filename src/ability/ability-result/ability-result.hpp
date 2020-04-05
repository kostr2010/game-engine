#pragma once

#include "../../entity/entity.hpp"

struct AbilityResult {
  public:
    EntityActive origin_;
};

struct AbilityResultPassive : public AbilityResult {
  public:
    AbilityKindPassive kind;
    EntityPassive      target_before;
    EntityPassive      target_after;
};

struct AbilityResultActive : public AbilityResult {
  public:
    AbilityKindActive kind;
    EntityActive      target_before;
    EntityActive      target_after;

    std::vector<AbilityResultActive>  sub_results_active;
    std::vector<AbilityResultPassive> sub_results_passive;
};