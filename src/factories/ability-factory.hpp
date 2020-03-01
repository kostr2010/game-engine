#pragma once
#include <cstdio>

#include "../main-classes/main-classes.hpp"

class Ability;

//====================
// CLASSES DECLARATION

//====================
// ability factory

class AbilityFactory {
  public:
    static Ability CreateAbilityDie(size_t hp_max, size_t hp_current);
    static Ability CreateAbilityKick(size_t damage);
    static Ability CreateAbilityPick();
    static Ability CreateAbilityLoot();
    static Ability CreateAbilityBePicked();
    static Ability CreateAbilityContain(size_t capacity);
    static Ability CreateAbilityMove();
    static Ability CreateAbilityHack(size_t hack_level);
    static Ability CreateAbilityBeLocked(size_t lock_level);
    static Ability CreateAbilityBeMap(size_t width, size_t height);

  private:
  protected:
};