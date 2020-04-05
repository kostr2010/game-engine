#pragma once

#include <map>
#include <vector>

#include "../entity/entity.hpp"

enum class EffectKind {
    stunned,
    shocked,
    crippled,
    poisoned,
    bleeding,
};

class Effect {
  public:
    Effect()  = default;
    ~Effect() = default;

    
    bool Apply(EntityActive& target);
    bool Apply(EntityPassive& target);

    bool Tick();

  private:
    bool (*dispatcher_active_)(EntityActive& target);
    bool (*dispatcher_passive_)(EntityPassive& target);

    int duration_;
    int strength_;
};