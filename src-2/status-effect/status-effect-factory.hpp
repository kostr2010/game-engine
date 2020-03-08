#pragma once

#include "status-effect.hpp"

class EffectFactory {
  public:
    static Effect CreatePoisonedEffect(int strength, int duration);
    static Effect CreateHealingEffect(int strength, int duration);
    static Effect CreateSlowedEffect(int strength, int duration);
    static Effect CreateCrippledEffect(int strength, int duration);
    static Effect CreateShockedEffect(int strength, int duration);
    static Effect CreateKnockedDownEffect(int strength, int duration);
    static Effect CreateBleedingEffect(int strength, int duration);

  private:
  protected:
};