#pragma once

#include "../entity/entity.hpp"

enum class EffectKind {
    Neutral,
    Poisoned,
    Healing,
    Slowed,
    Crippled,
    Shocked,
    KnockedDown,
    Bleeding,
};

class Effect {
  public:
    Effect(const EffectKind& effect_kind, int duration, int strength, bool (*dispatcher)(Entity& target));
    ~Effect() = default;

    int  GetEffectStrength() const;
    void SetEffectStrength(int strength_new);

    int  GetEffectDuration() const;
    void SetEffectDuration(int duration_new);

    bool Tick(Entity& target);

    EffectKind effect_kind_;

  private:
    int duration_;
    int strength_;
    bool (*dispatcher_)(Entity& target);

    bool Apply(Entity& target);

  protected:
};