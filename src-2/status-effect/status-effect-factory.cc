#include "status-effect-factory.hpp"

Effect EffectFactory::CreatePoisonedEffect(int strength, int duration) {
    Effect effect_poisoned(EffectKind::Poisoned, duration, strength, [](Entity& target) -> bool {
        // FIXME
        return true;
    });
}

Effect EffectFactory::CreateHealingEffect(int strength, int duration) {
}

Effect EffectFactory::CreateSlowedEffect(int strength, int duration) {
}

Effect EffectFactory::CreateCrippledEffect(int strength, int duration) {
}

Effect EffectFactory::CreateShockedEffect(int strength, int duration) {
}

Effect EffectFactory::CreateKnockedDownEffect(int strength, int duration) {
}

Effect EffectFactory::CreateBleedingEffect(int strength, int duration) {
}
