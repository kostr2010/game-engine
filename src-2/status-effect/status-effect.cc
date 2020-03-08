#include "status-effect.hpp"
#include <iostream>

Effect::Effect(const EffectKind& effect_kind, int duration, int strength,
               bool (*dispatcher)(Entity& target)) {
    effect_kind_ = effect_kind;
    duration_    = duration;
    strength_    = strength;
    dispatcher_  = dispatcher;
}

int Effect::GetEffectStrength() const {
    return strength_;
}
void Effect::SetEffectStrength(int strength_new) {
    strength_ = strength_new;
}

int Effect::GetEffectDuration() const {
    return duration_;
}

void Effect::SetEffectDuration(int duration_new) {
    duration_ = duration_new;
}

bool Effect::Tick(Entity& target) {
    if (--(duration_) > 0) {
        this->Apply(target);
        return true;
    } else
        return false;
};

bool Effect::Apply(Entity& target) {
    return dispatcher_(target);
}
